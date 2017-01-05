import unittest
from conans.test.tools import TestClient, TestServer
from conans.test.utils.test_files import hello_source_files
from conans.client.manager import CONANFILE
import os
from conans.model.ref import ConanFileReference, PackageReference
from conans.paths import CONAN_MANIFEST, CONANINFO
from conans.util.files import save
from conans.model.manifest import FileTreeManifest
from conans.client.proxy import ConanProxy


myconan1 = """
from conans import ConanFile
import platform

class HelloConan(ConanFile):
    name = "Hello"
    version = "1.2.1"
"""


class DownloadTest(unittest.TestCase):

    def complete_test(self):
        """ basic installation of a new conans
        """
        servers = {}
        # All can write (for avoid authentication until we mock user_io)
        test_server = TestServer([("*/*@*/*", "*")], [("*/*@*/*", "*")])
        servers["default"] = test_server

        conan_digest = FileTreeManifest(123123123, {})

        client = TestClient(servers=servers)
        client.init_dynamic_vars()
        conan_ref = ConanFileReference.loads("Hello/1.2.1@frodo/stable")
        reg_folder = client.paths.export(conan_ref)

        files = hello_source_files()
        client.save(files, path=reg_folder)
        client.save({CONANFILE: myconan1,
                     CONAN_MANIFEST: str(conan_digest),
                     "include/math/lib1.h": "//copy",
                     "my_lib/debug/libd.a": "//copy",
                     "my_data/readme.txt": "//copy"}, path=reg_folder)

        package_ref = PackageReference(conan_ref, "fakeid")
        package_folder = client.paths.package(package_ref)
        save(os.path.join(package_folder, CONANINFO), "info")
        save(os.path.join(package_folder, CONAN_MANIFEST), "manifest")
        save(os.path.join(package_folder, "include", "lib1.h"), "//header")
        save(os.path.join(package_folder, "lib", "my_lib", "libd.a"), "//lib")
        save(os.path.join(package_folder, "res", "shares", "readme.txt"),
             "//res")

        digest_path = client.client_cache.digestfile_package(package_ref)
        expected_manifest = FileTreeManifest.create(os.path.dirname(digest_path))
        save(os.path.join(package_folder, CONAN_MANIFEST), str(expected_manifest))

        client.run("upload %s" % str(conan_ref))
        client.run("upload %s -p %s" % (str(conan_ref), package_ref.package_id))

        client2 = TestClient(servers=servers)
        client2.init_dynamic_vars()

        installer = ConanProxy(client2.paths, client2.user_io, client2.remote_manager, "default")

        installer.get_recipe(conan_ref)
        installer.get_package(package_ref, force_build=False, short_paths=False, check_outdated=False)
        # Check that the output is done in order
        lines = [line.strip() for line in str(client2.user_io.out).splitlines()
                 if line.startswith("Downloading")]
        self.assertEqual(lines, ["Downloading conanmanifest.txt",
                                 "Downloading conanfile.py",
                                 "Downloading conan_export.tgz",
                                 "Downloading conanmanifest.txt",
                                 "Downloading conaninfo.txt",
                                 "Downloading conan_package.tgz"
                                 ])

        reg_path = client2.paths.export(ConanFileReference.loads("Hello/1.2.1/frodo/stable"))
        pack_folder = client2.paths.package(package_ref)

        # Test the file in the downloaded conans
        files = ['CMakeLists.txt',
                 'my_lib/debug/libd.a',
                 'hello.cpp',
                 'hello0.h',
                 CONANFILE,
                 CONAN_MANIFEST,
                 'main.cpp',
                 'include/math/lib1.h',
                 'my_data/readme.txt']

        for _file in files:
            self.assertTrue(os.path.exists(os.path.join(reg_path, _file)))
        self.assertTrue(os.path.exists(pack_folder))

        # Test the file in the downloaded package
        self.assertTrue(os.path.exists(pack_folder))
        self.assertTrue(os.path.exists(os.path.join(pack_folder, "include",
                                                    "lib1.h")))
        self.assertTrue(os.path.exists(os.path.join(pack_folder, "lib",
                                                    "my_lib/libd.a")))
        self.assertTrue(os.path.exists(os.path.join(pack_folder, "res",
                                                    "shares/readme.txt")))
