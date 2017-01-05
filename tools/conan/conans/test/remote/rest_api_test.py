import unittest
from conans.client.rest.rest_client import RestApiClient
from conans.model.ref import ConanFileReference, PackageReference
from conans.test.utils.test_files import hello_source_files
from conans.paths import CONANFILE, CONAN_MANIFEST, CONANINFO
import sys
from conans.client.output import ConanOutput, Color
from conans.model.info import ConanInfo
import os
import time
from conans.server.test.utils.server_launcher import TestServerLauncher
import requests
from conans.model.manifest import FileTreeManifest
from conans.util.files import md5
from conans.test.utils.test_files import temp_folder


class RestApiTest(unittest.TestCase):

    def setUp(self):
        self.server = TestServerLauncher()
        self.server.start()
        self.api = RestApiClient(ConanOutput(sys.stdout, Color), requester=requests)
        self.api.remote_url = "http://localhost:%s" % str(self.server.port)

        time.sleep(0.05)  # necessary in linux
        # Authenticate user
        token = self.api.authenticate("private_user", "private_pass")
        self.api.token = token
        self.local_folder = temp_folder()

    def tearDown(self):
        self.server.stop()

    def get_conan_test(self):
        # Upload a conans
        conan_reference = ConanFileReference.loads("conan1/1.0.0@private_user/testing")
        self._upload_conan(conan_reference)

        # Get the conans
        conan = self.api.get_conan(conan_reference)
        self.assertIsNotNone(conan)
        self.assertIn(CONANFILE, conan)
        self.assertIn(CONAN_MANIFEST, conan)

    def get_conan_digest_test(self):
        # Upload a conans
        conan_reference = ConanFileReference.loads("conan2/1.0.0@private_user/testing")
        self._upload_conan(conan_reference)

        # Get the conans digest
        digest = self.api.get_conan_digest(conan_reference)
        self.assertEquals(digest.sha, "thesha")
        self.assertEquals(digest.time, 123123123)

    def get_package_test(self):
        # Upload a conans
        conan_reference = ConanFileReference.loads("conan3/1.0.0@private_user/testing")
        self._upload_conan(conan_reference)

        # Upload an package
        package_reference = PackageReference(conan_reference, "1F23223EFDA")
        self._upload_package(package_reference)

        # Get the package
        package = self.api.get_package(package_reference)
        self.assertIsNotNone(package)
        self.assertIn("hello.cpp", package)

    def upload_huge_conan_test(self):
        # Upload a conans
        conan_reference = ConanFileReference.loads("conanhuge/1.0.0@private_user/testing")
        files = {"file%s.cpp" % name: "File conent" for name in range(1000)}
        self._upload_conan(conan_reference, files)

        # Get the conans
        pack = self.api.get_conan(conan_reference)
        self.assertIsNotNone(pack)
        self.assertIn("file999.cpp", pack)

    def search_test(self):
        # Upload a conan1
        conan_name1 = "HelloOnly/0.10@private_user/testing"
        conan_reference1 = ConanFileReference.loads(conan_name1)
        self._upload_conan(conan_reference1)

        # Upload an package
        conan_info = """[settings]
    arch: x86_64
    compiler: gcc
    os: Linux
[options]
    386: False
[requires]
    Hello
    Bye/2.9
    Say/2.1@user/testing
    Chat/2.1@user/testing:SHA_ABC
"""
        package_reference = PackageReference(conan_reference1, "1F23223EFDA")
        self._upload_package(package_reference, {CONANINFO: conan_info})

        # Upload a conan2
        conan_name2 = "helloonlyToo/2.1@private_user/stable"
        conan_reference2 = ConanFileReference.loads(conan_name2)
        self._upload_conan(conan_reference2)

        # Get the info about this ConanFileReference
        info = self.api.search("helloonly*")
        expected_info1 = {"1F23223EFDA": ConanInfo.loads(conan_info)}
        expected_info2 = {}
        self.assertEqual(expected_info1, info[conan_reference1])
        self.assertEqual(expected_info2, info[conan_reference2])

        # Get the info about this ConanFileReference
        info = self.api.search("HelloOnly*", ignorecase=False)
        expected_info = {"1F23223EFDA": ConanInfo.loads(conan_info)}
        self.assertEqual({conan_reference1: expected_info}, info)

    def remove_test(self):
        # Upload a conans
        conan_reference1 = ConanFileReference.loads("MyFirstConan/1.0.0@private_user/testing")
        self._upload_conan(conan_reference1)
        path1 = self.server.paths.conan(conan_reference1)
        self.assertTrue(os.path.exists(path1))
        # Remove conans and packages
        self.api.remove(conan_reference1)
        self.assertFalse(os.path.exists(path1))

    def remove_packages_test(self):
        conan_ref = ConanFileReference.loads("MySecondConan/2.0.0@private_user/testing")
        self._upload_conan(conan_ref)

        folders = {}
        for sha in ["1", "2", "3", "4", "5"]:
            # Upload an package
            package_ref = PackageReference(conan_ref, sha)
            self._upload_package(package_ref)
            folder = self.server.paths.package(package_ref)
            self.assertTrue(os.path.exists(folder))
            folders[sha] = folder

        self.api.remove_packages(conan_ref, ["1"])
        self.assertTrue(os.path.exists(self.server.paths.conan(conan_ref)))
        self.assertFalse(os.path.exists(folders["1"]))
        self.assertTrue(os.path.exists(folders["2"]))
        self.assertTrue(os.path.exists(folders["3"]))
        self.assertTrue(os.path.exists(folders["4"]))
        self.assertTrue(os.path.exists(folders["5"]))

        self.api.remove_packages(conan_ref, ["2", "3"])
        self.assertTrue(os.path.exists(self.server.paths.conan(conan_ref)))
        self.assertFalse(os.path.exists(folders["1"]))
        self.assertFalse(os.path.exists(folders["2"]))
        self.assertFalse(os.path.exists(folders["3"]))
        self.assertTrue(os.path.exists(folders["4"]))
        self.assertTrue(os.path.exists(folders["5"]))

        self.api.remove_packages(conan_ref)
        self.assertTrue(os.path.exists(self.server.paths.conan(conan_ref)))
        for sha in ["1", "2", "3", "4", "5"]:
            self.assertFalse(os.path.exists(folders[sha]))

    def _upload_package(self, package_reference, base_files=None):

        files = hello_source_files(3, [1, 12])
        if base_files:
            files.update(base_files)
        self.api.upload_package(package_reference, files)

    def _upload_conan(self, conan_reference, base_files=None):

        files = hello_source_files(3, [1, 12])
        if base_files:
            files.update(base_files)
        content = """
from conans import ConanFile

class MyConan(ConanFile):
    name = "%s"
    version = "%s"
    settings = arch, compiler, os
""" % (conan_reference.name, conan_reference.version)
        files[CONANFILE] = content
        files_md5s = {filename: md5(content) for filename, content in files.items()}
        conan_digest = FileTreeManifest(123123123, files_md5s)
        files[CONAN_MANIFEST] = str(conan_digest)

        self.api.upload_conan(conan_reference, files)
