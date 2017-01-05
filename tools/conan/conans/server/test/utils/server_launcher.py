#!/usr/bin/python
from conans.server.service.authorize import BasicAuthorizer, BasicAuthenticator
import os
from conans.server.conf import get_file_manager
from conans.server.rest.server import ConanServer
from conans.server.crypto.jwt.jwt_credentials_manager import JWTCredentialsManager
from conans.server.crypto.jwt.jwt_updown_manager import JWTUpDownAuthManager
from conans.util.log import logger
from conans.util.files import mkdir
from conans.test.utils.test_files import temp_folder
from conans.server.migrate import migrate_and_get_server_config
from conans.search import DiskSearchAdapter, DiskSearchManager
from conans.paths import SimplePaths


TESTING_REMOTE_PRIVATE_USER = "private_user"
TESTING_REMOTE_PRIVATE_PASS = "private_pass"


class TestServerLauncher(object):
    port = 0

    def __init__(self, base_path=None, read_permissions=None,
                 write_permissions=None, users=None, base_url=None, plugins=None,
                 server_version=None,
                 min_client_compatible_version=None):

        plugins = plugins or []
        if not base_path:
            base_path = temp_folder()

        if not os.path.exists(base_path):
            raise Exception("Base path not exist! %s")

        # Define storage_folder, if not, it will be readed from conf file and pointed to real user home
        storage_folder = os.path.join(base_path, ".conan_server", "data")
        mkdir(storage_folder)

        server_config = migrate_and_get_server_config(base_path, storage_folder)

        if TestServerLauncher.port == 0:
            TestServerLauncher.port = server_config.port

        # Encode and Decode signature for Upload and Download service
        updown_auth_manager = JWTUpDownAuthManager(server_config.updown_secret,
                                                   server_config.authorize_timeout)
        self.file_manager = get_file_manager(server_config, public_url=base_url,
                                             updown_auth_manager=updown_auth_manager)

        search_adapter = DiskSearchAdapter()
        self.search_manager = DiskSearchManager(SimplePaths(server_config.disk_storage_path), search_adapter)
        # Prepare some test users
        if not read_permissions:
            read_permissions = server_config.read_permissions
            read_permissions.append(("private_library/1.0.0@private_user/testing", "*"))
            read_permissions.append(("*/*@*/*", "*"))

        if not write_permissions:
            write_permissions = server_config.write_permissions

        if not users:
            users = dict(server_config.users)

        users[TESTING_REMOTE_PRIVATE_USER] = TESTING_REMOTE_PRIVATE_PASS

        authorizer = BasicAuthorizer(read_permissions, write_permissions)
        authenticator = BasicAuthenticator(users)
        credentials_manager = JWTCredentialsManager(server_config.jwt_secret,
                                                    server_config.jwt_expire_time)

        logger.debug("Storage path: %s" % storage_folder)
        self.port = TestServerLauncher.port
        TestServerLauncher.port += 1
        self.ra = ConanServer(self.port, False, credentials_manager, updown_auth_manager,
                              authorizer, authenticator, self.file_manager, self.search_manager, 
                              server_version, min_client_compatible_version)
        for plugin in plugins:
            self.ra.api_v1.install(plugin)

    def start(self, daemon=True):
        """from multiprocessing import Process
        self.p1 = Process(target=ra.run, kwargs={"host": "0.0.0.0"})
        self.p1.start()
        self.p1"""
        import threading
        self.t1 = threading.Thread(target=self.ra.run, kwargs={"host": "0.0.0.0"})
        self.t1.daemon = daemon
        self.t1.start()

    def stop(self):
        self.ra.root_app.close()


if __name__ == "__main__":
    server = TestServerLauncher()
    server.start(daemon=False)
