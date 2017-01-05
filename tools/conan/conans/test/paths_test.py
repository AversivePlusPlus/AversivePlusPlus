import os
import platform
import unittest
from conans.paths import (BUILD_FOLDER, PACKAGES_FOLDER, EXPORT_FOLDER, conan_expand_user,
                          SimplePaths, CONANINFO)
from conans.model.ref import ConanFileReference, PackageReference
from conans.test.utils.test_files import temp_folder
from conans.search import DiskSearchManager, DiskSearchAdapter
from conans.util.files import save
from conans.model.info import ConanInfo


class PathsTest(unittest.TestCase):

    def expand_user_test(self):
        if platform.system() == "Windows":
            old_env = dict(os.environ)
            try:
                os.environ["HOME"] = "%USERPROFILE%"
                user_home = conan_expand_user("~")
            finally:
                os.environ.clear()
                os.environ.update(old_env)
            self.assertTrue(os.path.exists(user_home))

    def basic_test(self):
        folder = temp_folder()
        paths = SimplePaths(folder)
        self.assertEqual(paths._store_folder, folder)
        conan_ref = ConanFileReference.loads("opencv/2.4.10 @ lasote /testing")
        package_ref = PackageReference(conan_ref, "456fa678eae68")
        expected_base = os.path.join(folder, os.path.sep.join(["opencv", "2.4.10",
                                                                    "lasote", "testing"]))
        self.assertEqual(paths.conan(conan_ref),
                         os.path.join(paths.store, expected_base))
        self.assertEqual(paths.export(conan_ref),
                         os.path.join(paths.store, expected_base, EXPORT_FOLDER))
        self.assertEqual(paths.build(package_ref),
                         os.path.join(paths.store, expected_base, BUILD_FOLDER,  "456fa678eae68"))
        self.assertEqual(paths.package(package_ref),
                         os.path.join(paths.store, expected_base, PACKAGES_FOLDER,
                                      "456fa678eae68"))

    def basic_test2(self):
        folder = temp_folder()
        paths = SimplePaths(folder)
        search_adapter = DiskSearchAdapter()
        search_manager = DiskSearchManager(paths, search_adapter)

        os.chdir(paths.store)

        root_folder1 = "opencv/2.4.10/lasote/testing"
        conan_ref1 = ConanFileReference.loads("opencv/2.4.10@lasote/testing")

        artif_id1 = "awqfwf44we5f425fw"
        artif_id2 = "b5wc4q5frg45rgv1g"
        artif_id3 = "cf838regrg783g453"

        reg1 = "%s/%s" % (root_folder1, EXPORT_FOLDER)
        build1 = "%s/%s/%s" % (root_folder1, BUILD_FOLDER, artif_id1)
        artif1 = "%s/%s/%s" % (root_folder1, PACKAGES_FOLDER, artif_id1)
        artif2 = "%s/%s/%s" % (root_folder1, PACKAGES_FOLDER, artif_id2)
        artif3 = "%s/%s/%s" % (root_folder1, PACKAGES_FOLDER, artif_id3)
        os.makedirs(reg1)
        os.makedirs(build1)
        os.makedirs(artif1)
        os.makedirs(artif2)
        os.makedirs(artif3)

        for package_path in [artif1, artif2, artif3]:
            info = ConanInfo().loads("[settings]\n[options]")
            save(os.path.join(paths.store, package_path, CONANINFO),
                 info.dumps())

        packages = search_manager.search_packages(conan_ref1, "")
        all_artif = [_artif for _artif in sorted(packages)]
        self.assertEqual(all_artif, [artif_id1, artif_id2, artif_id3])

        root_folder2 = "sdl/1.5/lasote/stable"
        conan_ref2 = ConanFileReference.loads("sdl/1.5@lasote/stable")
        os.makedirs("%s/%s" % (root_folder2, EXPORT_FOLDER))

        root_folder3 = "assimp/0.14/phil/testing"
        conan_ref3 = ConanFileReference.loads("assimp/0.14@phil/testing")
        os.makedirs("%s/%s" % (root_folder3, EXPORT_FOLDER))

        root_folder4 = "sdl/2.10/lasote/stable"
        conan_ref4 = ConanFileReference.loads("sdl/2.10@lasote/stable")
        os.makedirs("%s/%s" % (root_folder4, EXPORT_FOLDER))

        root_folder5 = "SDL_fake/1.10/lasote/testing"
        conan_ref5 = ConanFileReference.loads("SDL_fake/1.10@lasote/testing")
        os.makedirs("%s/%s" % (root_folder5, EXPORT_FOLDER))

        # Case insensitive searches
        search_adapter = DiskSearchAdapter()
        search_manager = DiskSearchManager(paths, search_adapter)

        reg_conans = sorted([str(_reg) for _reg in search_manager.search("*")])
        self.assertEqual(reg_conans, [str(conan_ref5),
                                      str(conan_ref3),
                                      str(conan_ref1),
                                      str(conan_ref2),
                                      str(conan_ref4)])

        reg_conans = sorted([str(_reg) for _reg in search_manager.search(pattern="sdl*")])
        self.assertEqual(reg_conans, [str(conan_ref5), str(conan_ref2), str(conan_ref4)])

        # Case sensitive search
        self.assertEqual(str(search_manager.search(pattern="SDL*", ignorecase=False)[0]),
                         str(conan_ref5))
