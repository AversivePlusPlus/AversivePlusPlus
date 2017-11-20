default_server_conf = """[server]
# WARNING! Change default variable of jwt_secret. You should change it periodically
# It only affects to current authentication tokens, you can change safetely anytime
# When it changes user are just forced to log in again
jwt_secret: {jwt_secret}
jwt_expire_minutes: 120

ssl_enabled: False
port: 9300
# Public port where files will be served. If empty will be used "port"
public_port:
host_name: localhost

# Choose file adapter, "disk" for disk storage
# Authorize timeout are seconds the client has to upload/download files until authorization expires
store_adapter: disk
authorize_timeout: 1800

# Just for disk storage adapter
# updown_secret is the key used to generate the upload/download authorization token
disk_storage_path: ~/.conan_server/data
disk_authorize_timeout: 1800
updown_secret: {updown_secret}


[write_permissions]

#
# name,version,user,channel: user1, user2, user3
# The rules are applied in order. If a rule applies to a conan, system wont look further.
#
# Example: All versions of opencv package from lasote user in testing channel is only
# writeable by default_user and default_user2. Rest of packages are not writtable by anything
# except the author.
#
#   "opencv/2.3.4@lasote/testing": default_user, default_user2
#

[read_permissions]

#
# name,version,user,channel: user1, user2, user3
# The rules are applied in order. If a rule applies to a conan, system wont look further.
#
# Example: All versions of opencv package from lasote user in testing channel is only
# readable by default_user and default_user2. Rest of packages are world readable
#
#   opencv/1.2.3@lasote/testing: default_user default_user2
#   *:*@*/*: *
#
# By default all users can read all blocks
*/*@*/*: *


[users]
#default_user: defaultpass
demo: demo
"""
