#!/usr/bin/env python3

import os
import sys
import json
import errno
import shutil
import typing
import inspect
import logging
import argparse
import subprocess
import multiprocessing

from pathlib import Path
from collections import OrderedDict
from dataclasses import dataclass, field
from typing import Callable, Iterable, Union, Tuple, Collection

from conan.api.subapi.profiles import Profile
from conan.api.conan_api import ConanAPI, ConanException
# this is not part of external API, but those formatters are really cool
from conan.cli.printers.graph import print_graph_basic
from conan.cli.printers import print_profiles


logger = logging.getLogger(__file__ if '__file__' in vars() else 'build.helper')


DESCRIPTION = '''
    CLI build helper.
'''


@dataclass
class Config:
    build_directory: Path = field(default_factory=lambda: Path.cwd().joinpath('build'))
    build_configs: Iterable[str] = field(default_factory=lambda: ['Debug'])
    cores: int = multiprocessing.cpu_count()
    generator: str = 'Ninja'
    # Conan-specific
    # build profile specifies target environment
    build_profile: str = 'default'
    # host profile describes host environment (where build happens)
    host_profile: str = 'default'


def routine(priority: int) -> Callable:
    def factory(f: Callable) -> Callable:
        f.priority = priority
        f.is_routine = True
        return f

    return factory


class Routines:
    CMAKE_USER_PRESETS = Path.cwd() / 'CMakeUserPresets.json'

    def __init__(self, params: Config):
        self.__params = params

    def routines(self) -> Iterable[Tuple[str, Callable]]:
        def key(pair):
            _, member = pair
            return member.priority if hasattr(member, 'priority') else 0

        members = inspect.getmembers(self, predicate=inspect.ismethod)
        for name, method in sorted(members, key=key, reverse=True):
            if hasattr(method, 'is_routine'):
                yield name, method

    @routine(5)
    def remove(self):
        for config in self.__params.build_configs:
            directory = self.__params.build_directory.joinpath(config)
            if directory.is_dir():
                logger.info(f'removing directory for CMake build config "{config}"')
                shutil.rmtree(directory)
            else:
                logger.error(f'build directory for config "{config}" was not found or was not a directory')

    @routine(4)
    def conan_install(self):
        api = ConanAPI()

        logger.debug(f'detected profiles: ' + ', '.join(api.profiles.list()))
        logger.info(
            'please notice, this script modifies "build_type" in incoming profile, to match running params'
        )
        remotes = api.remotes.list()

        for config in self.__params.build_configs:
            self._conan_install_for_config(config, api, remotes)

    @routine(3)
    def configure(self):
        if not self.__params.build_directory.is_dir():
            self.__params.build_directory.mkdir()

        use_presets = self.CMAKE_USER_PRESETS.is_file()
        if use_presets:
            logger.info('found CMake presets')
            presets = self._inspect_cmake_presets(self.CMAKE_USER_PRESETS)
            
            # make sure that presets are enabled for all possible cmake invocations (configure, build, test)
            preset_types = [key for key in presets if key.endswith('Presets')]

            presets_available = {}
            for config in self.__params.build_configs:
                presets_available[config] = all(f'conan-{config.lower()}' in presets[key] for key in preset_types)

        logger.info('configuring for CMake build configs: ' + ', '.join(self.__params.build_configs))

        for config in self.__params.build_configs:
            source = Path.cwd()
            binary = self.__params.build_directory.joinpath(config)

            command = [
                'cmake',
                '--preset', f'conan-{config.lower()}',
                '-G', self.__params.generator,
                '-B', str(binary),
                '-S', str(source),
                self._decorate_cmake_variable('CMAKE_EXPORT_COMPILE_COMMANDS', 'ON', 'BOOL'),
                self._decorate_cmake_variable('CMAKE_BUILD_TYPE', config)
            ] if use_presets else [
                'cmake',
                '-G', self.__params.generator,
                '-B', str(binary),
                '-S', str(source),
                self._decorate_cmake_variable('CMAKE_EXPORT_COMPILE_COMMANDS', 'ON', 'BOOL'),
                self._decorate_cmake_variable('CMAKE_BUILD_TYPE', config)
            ]

            logger.info(f'running configure command for CMake config {config}')
            self._run(command)

    @routine(2)
    def build(self):
        if not self.__params.build_directory.is_dir():
            raise FileNotFoundError(f'build directory \'{self.__params.build_directory}\' was not found')

        logger.info(f'using {self.__params.cores} threads')
        for config in self.__params.build_configs:
            directory = self.__params.build_directory.joinpath(config)
            logger.info(f'building for CMake configuration \'{config}\'')
            self._run([
                'cmake',
                '--build', str(directory),
                '--parallel', str(self.__params.cores)
            ])

    @routine(1)
    def symlink_compile_commands(self: 'Routines') -> None:
        path = None
        if 'Debug' in self.__params.build_configs:
            path = self.__params.build_directory.joinpath('Debug').joinpath('compile_commands.json')
            logger.info(f'creating symlink for path \'{path}\'')

        if 'Release' in self.__params.build_configs:
            path = self.__params.build_directory.joinpath('Release').joinpath('compile_commands.json')
            logger.info(f'creating symlink for path \'{path}\'')

        if path is None:
            raise ValueError('no supported CMake configs detected')

        symlink = Path.cwd().joinpath('compile_commands.json')
        if symlink.is_symlink():
            symlink.unlink()

        Path.cwd().joinpath('compile_commands.json').symlink_to(path)

    def _conan_install_for_config(
        self,
        config: str,
        api: ConanAPI,
        remotes: list
    ):        
        # fetch requested profiles
        try:
            # all profile tweaks should be done here, for some reason later modifications to Profile object
            # have no effect
            build_profile = api.profiles.get_profile([self.__params.build_profile], settings=[f'build_type={config}'])
            host_profile = api.profiles.get_profile([self.__params.host_profile], settings=[f'build_type={config}'])
            print_profiles(host_profile, build_profile)
        except ConanException as conan_error:
            raise RuntimeError(
                f'getting requested profiles failed: {(self.__params.build_profile, self.__params.host_profile)}'
            ) from conan_error

        logger.info(f'computing dependency graph for config: {config}')
        try:
            graph = api.graph.load_graph_consumer(
                path=api.local.get_conanfile_path('.', Path.cwd(), py=True),
                # these 4 are provided by recipe
                name=None,
                version=None,
                user=None,
                channel=None,
                # ==============================
                profile_build=build_profile,
                profile_host=host_profile,
                lockfile=None,
                remotes=remotes,
                update=True,
                check_updates=True
            )
            api.graph.analyze_binaries(graph, build_mode=['missing'], remotes=remotes, update=True)
            graph.report_graph_error()
            print_graph_basic(graph)

        except ConanException as conan_error:
            raise RuntimeError(
                f'failed to generate build graph, Conan API failed'
            ) from conan_error

        # make sure to define cmake layout in conanfile.py
        try:
            api.install.install_binaries(graph, remotes)
            api.install.install_consumer(graph, source_folder=Path.cwd())
        except ConanException as conan_error:
            raise RuntimeError(
                f'failed to install deps, Conan API failed'
            ) from conan_error

    def _inspect_cmake_presets(self, presets_file: Path) -> Collection[Tuple[str, dict]]:
        if not presets_file.is_file():
            raise FileNotFoundError(f'file "{presets_file}" does not exist')
        
        with open(presets_file, 'r') as fd:
            presets = json.load(fd)

        includes = presets['include']
        for file_to_include in map(Path, includes):
            if not file_to_include.is_absolute():
                file_to_include = presets_file.parent / file_to_include

            with open(file_to_include, 'r') as file:
                contents = json.load(file)

            for key in contents:
                if key.endswith('Presets'):
                    if key not in presets:
                        presets[key] = []

                    # FIXME: probably should prefer initial values if set
                    presets[key].append(contents[key])
            
        return presets

    def _run(self: 'Routines', command: typing.List[str]) -> None:
        logger.info('running command: ' + ' '.join(command))
        code = subprocess.run(command, encoding='UTF-8', stderr=subprocess.STDOUT, env=os.environ).returncode
        if code:
            sys.exit(f'error: subprocess failed: {errno.errorcode[code]} (code: {code})')

    def _decorate_cmake_variable(self: 'Routines', var: str, value: str, type: Union[str, None] = None) -> str:
        if type is not None:
            return f'-D{var.upper()}:{type}={value}'
        return f'-D{var.upper()}={value}'


def parse_cli_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=DESCRIPTION, formatter_class=argparse.RawDescriptionHelpFormatter)
    # Routines
    parser.add_argument('-b', '--build', action='store_true', dest='build')
    parser.add_argument('-c', '--configure', action='store_true', dest='configure')
    parser.add_argument('-i', '--conan-install', action='store_true', dest='conan_install')
    parser.add_argument('-r', '--remove', action='store_true', dest='remove')
    parser.add_argument('-l', '--symlink-compile-commands', action='store_true', dest='symlink_compile_commands')
    # Environment
    parser.add_argument('--build-dir', action='store', dest='build_directory')
    parser.add_argument('--config', action='append', dest='configs', choices=['Debug', 'Release'])
    parser.add_argument('--parallel', action='store', dest='cores')
    parser.add_argument('--generator', action='store', dest='generator')
    parser.add_argument('--profile', action='store', dest='profile')
    return parser.parse_args()


def main():
    try:
        from rich.logging import RichHandler
        from rich.traceback import install

        install(show_locals=True)
        handler = RichHandler(
            level=logging.DEBUG,
            rich_tracebacks=True,
            show_path=False,
            show_time=False,
            show_level=True,
        )
    except ImportError:
        handler = logging.StreamHandler(sys.stdout)

    logging.root.addHandler(handler)
    logging.root.setLevel(logging.INFO)

    args = parse_cli_args()

    params = Config()
    if getattr(args, 'build_directory') is not None:
        params.build_directory = Path.cwd().joinpath(args.build_directory)
        logger.info(f'config: user-provided build directory: "{params.build_directory}"')
    if getattr(args, 'configs') is not None:
        params.build_configs = args.configs
        logger.info(f'config: user-provided build configs: {params.build_configs}')
    if getattr(args, 'cores') is not None:
        params.cores = int(args.cores)
        logger.info(f'config: user-provided threads, that will be run in parallel: "{params.cores}"')
    if getattr(args, 'profile') is not None:
        params.profile = args.profile
        logger.info(f'config: user-provided conan profile: "{params.profile}"')
    if getattr(args, 'generator') is not None:
        params.generator = args.generator
        logger.info(f'config: user-provided generator: "{params.generator}"')

    r = Routines(params)
    for routine, f in r.routines():
        if not hasattr(args, routine):
            logger.info(f'routine \'{routine}\' is not configured for CLI, skipping')
            continue
        if getattr(args, routine):
            logger.info(f'running {routine}')
            f()

    logger.info('done!')


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print('exited by user')