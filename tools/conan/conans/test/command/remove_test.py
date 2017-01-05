import unittest
from conans.test.tools import TestClient, TestBufferConanOutput, TestServer
from conans.paths import PACKAGES_FOLDER, EXPORT_FOLDER, BUILD_FOLDER, SRC_FOLDER, CONANFILE,\
    CONAN_MANIFEST, CONANINFO
import os
from mock import Mock
from conans.client.userio import UserIO
from conans.test.utils.test_files import temp_folder
import six
from conans.test.utils.cpp_test_files import cpp_hello_conan_files
from conans.model.ref import PackageReference, ConanFileReference
from conans.model.manifest import FileTreeManifest


class RemoveTest(unittest.TestCase):

    def setUp(self):
        hello_files = cpp_hello_conan_files("Hello")
        test_conanfile_contents = hello_files[CONANFILE]

        self.server_folder = temp_folder()
        test_server = TestServer(users={"fenix": "mypass"},
                                 base_path=self.server_folder)  # exported users and passwords
        self.server = test_server
        servers = {"default": test_server}
        client = TestClient(servers=servers, users={"default": [("fenix", "mypass")]})

        # Conans with and without packages created
        self.root_folder = {"H1": 'Hello/1.4.10/fenix/testing',
                            "H2": 'Hello/2.4.11/fenix/testing',
                            "B": 'Bye/0.14/fenix/testing',
                            "O": 'Other/1.2/fenix/testing'}

        files = {}
        pack_refs = []
        for key, folder in self.root_folder.items():
            ref = ConanFileReference.loads(folder)
            files["%s/%s/conanfile.py" % (folder, EXPORT_FOLDER)] = test_conanfile_contents
            files["%s/%s/conanmanifest.txt" % (folder, EXPORT_FOLDER)] = ""
            files["%s/%s/conans.txt" % (folder, SRC_FOLDER)] = ""
            for pack_id in (1, 2):
                pack_id = "%s_%s" % (pack_id, key)
                pack_refs.append(PackageReference(ref, str(pack_id)))
                files["%s/%s/%s/conans.txt" % (folder, BUILD_FOLDER, pack_id)] = ""
                files["%s/%s/%s/conans.txt" % (folder, PACKAGES_FOLDER, pack_id)] = ""
                files["%s/%s/%s/%s" % (folder, PACKAGES_FOLDER, pack_id, CONANINFO)] = ""
                files["%s/%s/%s/%s" % (folder, PACKAGES_FOLDER, pack_id, CONAN_MANIFEST)] = ""

        client.save(files, client.client_cache.store)

        # Create the manifests to be able to upload
        for pack_ref in pack_refs:
            digest_path = client.client_cache.digestfile_package(pack_ref)
            expected_manifest = FileTreeManifest.create(os.path.dirname(digest_path))
            files["%s/%s/%s/%s" % ("/".join(pack_ref.conan),
                                   PACKAGES_FOLDER,
                                   pack_ref.package_id,
                                   CONAN_MANIFEST)] = str(expected_manifest)

        client.save(files, client.client_cache.store)

        self.client = client

        for folder in self.root_folder.values():
            client.run("upload %s --all" % folder.replace("/fenix", "@fenix"))

        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})

    def assert_folders(self, local_folders, remote_folders, build_folders, src_folders):
        for base_path, folders in [(self.client.paths, local_folders),
                                   (self.server.paths, remote_folders)]:
            root_folder = base_path.store
            for k, shas in folders.items():
                folder = os.path.join(root_folder, self.root_folder[k])
                if shas is None:
                    self.assertFalse(os.path.exists(folder))
                else:
                    for value in (1, 2):
                        sha = "%s_%s" % (value, k)
                        package_folder = os.path.join(folder, "package", sha)
                        if value in shas:
                            self.assertTrue(os.path.exists(package_folder))
                        else:
                            self.assertFalse(os.path.exists(package_folder))

        root_folder = self.client.paths.store
        for k, shas in build_folders.items():
            folder = os.path.join(root_folder, self.root_folder[k])
            if shas is None:
                self.assertFalse(os.path.exists(folder))
            else:
                for value in (1, 2):
                    sha = "%s_%s" % (value, k)
                    build_folder = os.path.join(folder, "build", sha)
                    if value in shas:
                        self.assertTrue(os.path.exists(build_folder))
                    else:
                        self.assertFalse(os.path.exists(build_folder))
        for k, value in src_folders.items():
            folder = os.path.join(root_folder, self.root_folder[k], "source")
            if value:
                self.assertTrue(os.path.exists(folder))
            else:
                self.assertFalse(os.path.exists(folder))

    def basic_test(self):
        self.client.run("remove hello/* -f")
        self.assert_folders({"H1": None, "H2": None, "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": None, "H2": None, "B": [1, 2], "O": [1, 2]},
                            {"H1": False, "H2": False, "B": True, "O": True})
        folders = os.listdir(self.client.storage_folder)
        six.assertCountEqual(self, ["Other", "Bye"], folders)

    def basic_mocked_test(self):
        mocked_user_io = UserIO(out=TestBufferConanOutput())
        mocked_user_io.request_boolean = Mock(return_value=True)
        self.client.run("remove hello/*", user_io=mocked_user_io)
        self.assert_folders({"H1": None, "H2": None, "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": None, "H2": None, "B": [1, 2], "O": [1, 2]},
                            {"H1": False, "H2": False, "B": True, "O": True})
        folders = os.listdir(self.client.storage_folder)
        six.assertCountEqual(self, ["Other", "Bye"], folders)

    def basic_packages_test(self):
        self.client.run("remove hello/* -p -f")
        self.assert_folders({"H1": [], "H2": [], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})
        folders = os.listdir(self.client.storage_folder)
        six.assertCountEqual(self, ["Hello", "Other", "Bye"], folders)
        six.assertCountEqual(self, ["build", "source", "export"],
                              os.listdir(os.path.join(self.client.storage_folder,
                                                      "Hello/1.4.10/fenix/testing")))
        six.assertCountEqual(self, ["build", "source", "export"],
                              os.listdir(os.path.join(self.client.storage_folder,
                                                      "Hello/2.4.11/fenix/testing")))

    def builds_test(self):
        mocked_user_io = UserIO(out=TestBufferConanOutput())
        mocked_user_io.request_boolean = Mock(return_value=True)
        self.client.run("remove hello/* -b", user_io=mocked_user_io)
        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [], "H2": [], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})
        folders = os.listdir(self.client.storage_folder)
        six.assertCountEqual(self, ["Hello", "Other", "Bye"], folders)
        six.assertCountEqual(self, ["package", "source", "export"],
                              os.listdir(os.path.join(self.client.storage_folder,
                                                      "Hello/1.4.10/fenix/testing")))
        six.assertCountEqual(self, ["package", "source", "export"],
                              os.listdir(os.path.join(self.client.storage_folder,
                                                      "Hello/2.4.11/fenix/testing")))

    def src_test(self):
        mocked_user_io = UserIO(out=TestBufferConanOutput())
        mocked_user_io.request_boolean = Mock(return_value=True)
        self.client.run("remove hello/* -s", user_io=mocked_user_io)
        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": False, "H2": False, "B": True, "O": True})
        folders = os.listdir(self.client.storage_folder)
        six.assertCountEqual(self, ["Hello", "Other", "Bye"], folders)
        six.assertCountEqual(self, ["package", "build", "export"],
                              os.listdir(os.path.join(self.client.storage_folder,
                                                      "Hello/1.4.10/fenix/testing")))
        six.assertCountEqual(self, ["package", "build", "export"],
                              os.listdir(os.path.join(self.client.storage_folder,
                                                      "Hello/2.4.11/fenix/testing")))

    def reject_removal_test(self):
        mocked_user_io = UserIO(out=TestBufferConanOutput())
        mocked_user_io.request_boolean = Mock(return_value=False)
        self.client.run("remove hello/* -s -b -p", user_io=mocked_user_io)
        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})

    def remote_build_error_test(self):
        self.client.run("remove hello/* -b -r=default", ignore_error=True)
        self.assertIn("Remotes don't have 'build' or 'src' folder", self.client.user_io.out)
        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})

    def remote_packages_test(self):
        self.client.run("remove hello/* -p -r=default -f")
        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [], "H2": [], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})

    def remote_conans_test(self):
        self.client.run("remove hello/* -r=default -f")
        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": None, "H2": None, "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})
        remote_folder = os.path.join(self.server_folder, ".conan_server/data") 
        folders = os.listdir(remote_folder)
        six.assertCountEqual(self, ["Other", "Bye"], folders)

    def remove_specific_package_test(self):
        self.client.run("remove hello/1.4.10* -p=1_H1 -f")
        self.assert_folders({"H1": [2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})

    def remove_specific_packages_test(self):
        self.client.run("remove hello/1.4.10* -p=1_H1,2_H1 -f")
        self.assert_folders({"H1": [], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})

    def remove_specific_build_test(self):
        self.client.run("remove hello/1.4.10* -b=1_H1 -f")
        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})

    def remove_specific_builds_test(self):
        self.client.run("remove hello/1.4.10* -b=1_H1,2_H1 -f")
        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})

    def remove_remote_specific_package_test(self):
        self.client.run("remove hello/1.4.10* -p=1_H1 -f -r=default")
        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})

    def remove_remote_specific_packages_test(self):
        self.client.run("remove hello/1.4.10* -p=1_H1,2_H1 -f -r=default")
        self.assert_folders({"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": [1, 2], "H2": [1, 2], "B": [1, 2], "O": [1, 2]},
                            {"H1": True, "H2": True, "B": True, "O": True})
