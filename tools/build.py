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
from typing import Callable, Iterable, Union, Tuple, Collection, Optional

from conan.api.conan_api import ConanAPI, ConanException
# this is not part of external API, but those formatters are really cool
from conan.api.output import ConanOutput
from conan.cli.printers import print_profiles
from conan.cli.printers.graph import print_graph_basic, print_graph_packages


logger = logging.getLogger(__file__ if '__file__' in vars() else 'build.helper')


DESCRIPTION = '''
    CLI build helper.
'''


@dataclass
class Config:
    build_directory: Path = field(default_factory=lambda: Path.cwd().joinpath('build'))
    cores: int = multiprocessing.cpu_count()
    # CMake-specific
    build_configs: Iterable[str] = field(default_factory=lambda: ['Debug'])
    generator: Optional[str] = None
    defines: Collection[Tuple[str, str, str]] = field(default_factory=lambda: [])
    # Conan-specific
    # allow conan to detect profile (might be inaccurate)
    allow_profile_detection: bool = False
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
        api = ConanAPI(str(self.__params.build_directory / 'conan2'))

        detect_profiles = False
        profiles = api.profiles.list()
        if len(profiles) > 0:
            logger.debug(f'detected profiles: ' + ', '.join(profiles))
        else:
            if not self.__params.allow_profile_detection:
                raise FileNotFoundError(
                    'no profiles exist and autodetection is turned off'
                )
            detect_profiles = True

        logger.info(
            'please notice, this script modifies "build_type" in incoming profile, to match running params'
        )
        remotes = api.remotes.list()

        for config in self.__params.build_configs:
            if not self._conan_install_for_config(config, api, remotes, detect_profiles=detect_profiles):
                raise RuntimeError(
                    f'failed to install dependencies for config: {config}, see error from conan above'
                )

    @routine(3)
    def configure(self):
        if not self.__params.build_directory.is_dir():
            self.__params.build_directory.mkdir()

        use_presets = Path.cwd().joinpath('CMakeUserPresets.json').is_file()
        if use_presets:
            logger.info('found CMake presets')

        logger.info('configuring for CMake build configs: ' + ', '.join(self.__params.build_configs))
        for config in self.__params.build_configs:
            source = Path.cwd()
            binary = self.__params.build_directory.joinpath(config)

            # TODO: allow multiconfigs
            command = [
                'cmake',
                '--preset', f'conan-{config.lower()}',
                '-B', str(binary),
                '-S', str(source),
                self._decorate_cmake_variable('CMAKE_EXPORT_COMPILE_COMMANDS', 'ON', 'BOOL'),
                self._decorate_cmake_variable('CMAKE_BUILD_TYPE', config)
            ] if use_presets else [
                'cmake',
                '-B', str(binary),
                '-S', str(source),
                self._decorate_cmake_variable('CMAKE_EXPORT_COMPILE_COMMANDS', 'ON', 'BOOL'),
                self._decorate_cmake_variable('CMAKE_BUILD_TYPE', config)
            ]

            if self.__params.generator is not None:
                command.extend(['-G', self.__params.generator])

            if len(self.__params.defines) > 0:
                for key, var_type, value in self.__params.defines:
                    command.append(self._decorate_cmake_variable(key, value, var_type))

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
        remotes: list,
        detect_profiles: bool = False
    ) -> bool:
        out = ConanOutput()
        try:
            if detect_profiles:
                build_profile = host_profile = api.profiles.detect()
            else:
                build_profile = api.profiles.get_profile([self.__params.build_profile])
                host_profile = api.profiles.get_profile([self.__params.host_profile])

            mixin = OrderedDict({'build_type': config})
            for profile in (build_profile, host_profile):
                profile.update_settings(mixin)
                if profile.processed_settings is None:
                    profile.process_settings(api.config.settings_yml)

            if detect_profiles:
                out.title('Autodetected profiles (be careful using them!)')
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
            print_graph_basic(graph)
            graph.report_graph_error()
            api.graph.analyze_binaries(graph, build_mode=['missing'], remotes=remotes, update=True)
            print_graph_packages(graph)

        except ConanException as conan_error:
            out.error(str(conan_error))
            return False

        # make sure to define cmake layout in conanfile.py
        try:
            api.install.install_binaries(graph, remotes)
            api.install.install_consumer(graph, source_folder=Path.cwd())
        except ConanException as conan_error:
            out.error(str(conan_error))
            return False
        
        return True

    def _run(self: 'Routines', command: typing.List[str]) -> None:
        logger.info('running command: ' + ' '.join(command))
        code = subprocess.run(command, encoding='UTF-8', stderr=subprocess.STDOUT, env=os.environ).returncode
        if code:
            sys.exit(f'error: subprocess failed: {errno.errorcode[code]} (code: {code})')

    def _decorate_cmake_variable(self: 'Routines', var: str, value: str, var_type: Union[str, None] = None) -> str:
        if var_type is not None:
            return f'-D{var.upper()}:{var_type}={value}'
        return f'-D{var.upper()}={value}'
    

def resolve_profiles(config: Config, args: argparse.Namespace):
    if args.profile_all is not None:
        config.build_profile = config.host_profile = args.profile_all
        logger.info(f'using specified "all" (build and host) profile: {args.profile_all}')
        return
    
    if args.profile_host is not None:
        config.host_profile = args.profile_host
        logger.info(f'using specified "host" profile: {args.profile_host}')

    if args.profile_build is not None:
        config.build_profile = args.profile_build
        logger.info(f'using specified "host" profile: {args.profile_build}')
    
    if all(profile is None for profile in (args.profile_all, args.profile_host, args.profile_build)):
        logger.info('no profiles were specified. Using default for both "host" and "build"')


def resolve_defines(config: Config, args: argparse.Namespace):
    for define in args.defines:
        name, value = define.split('=')
        var_name, var_type = name.split(':')
        config.defines.append((var_name, var_type, value))


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
    # TODO: allow more configs
    parser.add_argument('--config', action='append', dest='configs', choices=['Debug', 'Release'])
    parser.add_argument('--parallel', action='store', dest='cores')
    parser.add_argument('--generator', action='store', dest='generator')
    # Profiles
    parser.add_argument('--pr:a', action='store', dest='profile_all')
    parser.add_argument('--pr:h', action='store', dest='profile_host')
    parser.add_argument('--pr:b', action='store', dest='profile_build')
    parser.add_argument('--profiles-detection', action='store_true', dest='profile_detect')
    # Arbitrary CMake flags
    parser.add_argument('-D', metavar='KEY:TYPE=VALUE', action='append', default=[], dest='defines')
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
    if getattr(args, 'generator') is not None:
        params.generator = args.generator
        logger.info(f'config: user-provided generator: "{params.generator}"')
    params.allow_profile_detection = args.profile_detect

    resolve_profiles(params, args)
    resolve_defines(params, args)

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