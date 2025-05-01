import os
import logging
import unittest

from pathlib import Path
from scripts.build import Routines, Config

# TODO: make a single test runner
# TODO: add more tests + run resulting executable
class BuildsystemTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.dummy_message = 'Hello, HyperCPU!'
        cls.orig_cwd = Path.cwd()
        cls.dummy_dir = cls.orig_cwd / 'DummyProject'
        
        os.chdir(cls.dummy_dir)

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
        path.mkdir(parents=True, exist_ok=True)

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
            path.mkdir(parents=True, exist_ok=True)

        self.config.build_configs = ['Debug', 'Release']
        self.routines.remove()

        debug, release = paths
        # it is important to preserve top-level "build" dir
        self.assertTrue(build_path.exists())
        self.assertFalse(debug.exists())
        self.assertFalse(release.exists())

    def test_02_conan_install(self):
        # it just has to work
        self.config.allow_profile_detection = True
        self.config.build_configs = ['Debug', 'Release']
        self.routines.conan_install()

        build_path = self.config.build_directory
        debug, release = build_path / 'Debug', build_path / 'Release'
        self.assertTrue(build_path.exists())
        self.assertTrue(debug.exists())
        self.assertTrue(release.exists())

    def test_03_configure(self):
        self.config.defines.append(
            ('DUMMY_MESSAGE', 'STRING', self.dummy_message)
        )
        self.config.build_configs = ['Debug', 'Release']
        self.routines.configure()

    def test_04_build(self):
        self.config.build_configs = ['Debug', 'Release']
        self.routines.build()
        pass

    def test_05_symlink_debug_compile_commands(self):
        pass
        pass

if __name__ == '__main__':
    logging.basicConfig(level=logging.DEBUG)
    unittest.main()