from typing import Self, List
from functools import lru_cache

from conan import ConanFile
from conan.tools.cmake import cmake_layout


class HyperCPU(ConanFile):
    generators: List[str] = ['CMakeToolchain', 'CMakeDeps']
    settings: List[str] = ['os', 'compiler', 'build_type', 'arch']

    def __init__(self: Self, display_name: str = '') -> None:
        self.name = 'HyperCPU'

        self.__requirements = {
            'gtest': '1.14.0',
            'benchmark': '1.9.1',
            'abseil': '20250127.0',
            'libbacktrace': 'cci.20240730',
            'argparse': '3.2',
            'eternal': '1.0.1',
            're2': '20240702',
            'fmt': '11.1.4',
            'libunwind': '1.8.1'
        }
        super().__init__(display_name)

    @lru_cache
    def requirements(self: Self) -> None:
        for req, version in self.__requirements.items():
            self.requires(f'{req}/{version}')

    def layout(self):
        cmake_layout(self)
