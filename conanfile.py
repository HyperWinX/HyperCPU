from typing import Dict, Any, Collection
from functools import cached_property, lru_cache

from conan import ConanFile
from conan.tools.google import bazel_layout


class HyperCPU(ConanFile):
    name: "HyperCPU"
    settings = ["os", "compiler", "build_type", "arch"]

    # conan data is fetched dynamically from
    # conandata.yml
    conan_data: Dict[str, Any]

    @cached_property
    def generators(self) -> Collection[str]:
        return ["BazelToolchain", "BazelDeps"]

    @lru_cache
    def requirements(self) -> None:
        for req, version in self.conan_data["requirements"].items():
            self.requires(f"{req}/{version}")

    def layout(self):
        bazel_layout(self)
