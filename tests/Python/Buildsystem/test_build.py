import os
import unittest

from pathlib import Path
from scripts.build import Routines, Config


class BuildsystemTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.orig_cwd = Path.cwd()
        dummy_dir = cls.orig_cwd / 'dummy'
        os.chdir(dummy_dir)

    @classmethod
    def tearDownClass(cls):
        os.chdir(cls.orig_cwd)

    def setUp(self):
        self.config = Config()
        self.routines = Routines(self.config)

    def test_01_remove_no_dirs(self):
        self.config.build_configs = ['Debug', 'Release']
        self.routines.remove()

    def test_01_remove_a_single_dir(self):
        path = self.config.build_directory / 'Debug'
        path.mkdir(parents=True)

        self.config.build_configs = ['Debug']
        self.routines.remove()

        self.assertFalse(path.exists())

    def test_01_remove_selected_dir(self):
        build_path = self.config.build_directory
        paths = [build_path / 'Debug', build_path / 'Release']
        for path in paths:
            path.mkdir(parents=True)

        self.config.build_configs = ['Debug']
        self.routines.remove()

        debug, release = paths
        self.assertTrue(build_path.exists())
        self.assertFalse(debug.exists())
        self.assertTrue(release.exists())

    def test_01_remove_all_dirs(self):
        build_path = self.config.build_directory
        paths = [build_path / 'Debug', build_path / 'Release']
        for path in paths:
            path.mkdir(parents=True)

        self.config.build_configs = ['Debug', 'Release']
        self.routines.remove()

        debug, release = paths
        # it is important to preserve top-level "build" dir
        self.assertTrue(build_path.exists())
        self.assertFalse(debug.exists())
        self.assertFalse(release.exists())

    def test_02_conan_install(self):
        # it just has to work
        self.config.build_configs = ['Debug', 'Release']
        self.routines.conan_install()

        # TODO: check presets?

        build_path = self.config.build_directory
        debug, release = build_path / 'Debug', build_path / 'Release'
        self.assertTrue(build_path.exists())
        self.assertTrue(debug.exists())
        self.assertTrue(release.exists())

    def test_03_configure(self):
        # TODO: stub out subprocess calls and verify configure() constructs correct cmake commands.
        pass

    def test_04_build(self):
        # TODO: create dummy build/Debug directory and test build() calls cmake --build with correct args.
        pass

    def test_05_symlink_compile_commands(self):
        # TODO: create compile_commands.json in build/Debug or build/Release,
        # and test symlink_compile_commands() creates the top-level symlink correctly.
        pass

if __name__ == '__main__':
    unittest.main()