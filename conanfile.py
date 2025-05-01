import enum

from functools import cached_property, lru_cache
from typing import Dict, Any, Collection, Mapping, Callable, Optional, cast

from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.google import bazel_layout
from conan.errors import ConanInvalidConfiguration


class Buildsystem(enum.StrEnum):
    CMAKE = 'cmake'
    BAZEL = 'bazel'


class HyperCPU(ConanFile):
    name: 'HyperCPU'
    # generators =
    settings = ['os', 'compiler', 'build_type', 'arch']

    # conan data is fetched dynamically from
    # conandata.yml
    conan_data: Dict[str, Any]

    @cached_property
    def generators(self) -> Collection[str]:
        return cast(Collection[str], self.__resolve_buildsystem({
            Buildsystem.CMAKE: lambda _: ['CMakeToolchain', 'CMakeDeps'],
            Buildsystem.BAZEL: lambda _: ['BazelToolchain', 'BazelDeps']
        }))

    @lru_cache
    def requirements(self) -> None:
        for req, version in self.conan_data['requirements'].items():
            self.requires(f'{req}/{version}')

    def layout(self):
        self.__resolve_buildsystem({
            Buildsystem.CMAKE: lambda self: cmake_layout(self),
            Buildsystem.BAZEL: lambda self: bazel_layout(self)
        })

    def __resolve_buildsystem(
        self,
        visitors: Mapping[Buildsystem, Callable[['HyperCPU'], Optional[Any]]]
    ) -> Optional[Any]:
        buildsystem = Buildsystem(self.conan_data['buildsystem'])
        if buildsystem not in visitors:
            raise ConanInvalidConfiguration(
                f'buildsystem: {buildsystem} is not supported by visitors: ' + ', '.join(visitors)
            )

        return visitors[buildsystem](self)
