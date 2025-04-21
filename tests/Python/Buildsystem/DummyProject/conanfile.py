from typing import Self, List

from conan import ConanFile
from conan.tools.cmake import cmake_layout


class Dummy(ConanFile):
    generators: List[str] = ['CMakeToolchain', 'CMakeDeps']
    settings: List[str] = ['os', 'compiler', 'build_type', 'arch']

    def __init__(self: Self, display_name: str = '') -> None:
        self.name = 'Dummy'
        self.version = '1.0.0'
        super().__init__(display_name)

    def requirements(self: Self) -> None:
        self.requires('plog/1.1.10')

    def layout(self):
        cmake_layout(self)