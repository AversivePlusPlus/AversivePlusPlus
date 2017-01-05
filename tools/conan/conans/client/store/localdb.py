from conans.client.store.sqlite import SQLiteDB
from conans.errors import ConanException

USER_TABLE = "users"  # conan retrocompatibility
REMOTES_USER_TABLE = "users_remotes"


class LocalDB(SQLiteDB):

    def __init__(self, dbfile):
        self.dbfile = dbfile
        super(LocalDB, self).__init__(dbfile)
        self.connect()
        self.init()

    def init(self, clean=False):
        SQLiteDB.init(self)
        cursor = None
        try:
            cursor = self.connection.cursor()
            # conan retrocompatibility
            cursor.execute("drop table if exists %s" % USER_TABLE)
            if clean:
                cursor.execute("drop table if exists %s" % REMOTES_USER_TABLE)
            cursor.execute("create table if not exists %s "
                           "(remote_url TEXT UNIQUE, user TEXT, token TEXT)" % REMOTES_USER_TABLE)
        except Exception as e:
            message = "Could not initialize local sqlite database"
            raise ConanException(message, e)
        finally:
            if cursor:
                cursor.close()

    def get_login(self, remote_url):
        '''Returns login credentials.
        This method is also in charge of expiring them.
        '''
        try:
            statement = self.connection.cursor()
            statement.execute('select user, token from %s where remote_url="%s"'
                              % (REMOTES_USER_TABLE, remote_url))
            rs = statement.fetchone()
            if not rs:
                return None, None
            name = rs[0]
            token = rs[1]
            return name, token
        except Exception:
            raise ConanException("Couldn't read login\n Try removing '%s' file" % self.dbfile)

    def get_username(self, remote_url):
        return self.get_login(remote_url)[0]

    def set_login(self, login, remote_url):
        """Login is a tuple of (user, token)"""
        try:
            statement = self.connection.cursor()
            statement.execute("INSERT OR REPLACE INTO %s (remote_url, user, token) "
                              "VALUES (?, ?, ?)" % REMOTES_USER_TABLE,
                              (remote_url, login[0], login[1]))
            self.connection.commit()
        except Exception as e:
            raise ConanException("Could not store credentials %s" % str(e))
