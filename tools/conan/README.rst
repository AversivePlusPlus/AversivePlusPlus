Conan
=====

A distributed, open source, package manager.

+------------------------+-------------------------+----------------------+-----------------------+
| **master (linux/osx)** | **develop (linux/osx)** | **master (windows)** | **develop** (windows) |
+========================+=========================+======================+=======================+
| |Build Status1|        | |Build Status2|         | |Build status3|      | |Build status4|       |
+------------------------+-------------------------+----------------------+-----------------------+

Setup
=====

From binaries
-------------

We have installers for `most platforms here <http://conan.io>`__ but you
can run **conan** from sources if you want


From pip
--------

Conan is compatible with Python 2 and Python 3.

- Install pip following `pip docs`_

- Install conan:

::

    $ pip install conan


From Homebrew (OSx)
-------------------

- Install Homebrew following `brew homepage`_.

::

    $ brew update
    $ brew install conan



From source
-----------

You can run **conan** client and server in Windows, MacOS, and Linux.

Install *python and pip*, search in google instructions for your operating system.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Clone conan repository
~~~~~~~~~~~~~~~~~~~~~~

::

    $ git clone https://github.com/conan-io/conan.git

Install python requirements
~~~~~~~~~~~~~~~~~~~~~~~~~~~

For running the client:

::

    $ sudo pip install -r conans/requirements.txt

Server:

::

    $ sudo apt-get install python-dev
    $ sudo pip install -r conans/requirements_server.txt

Development:

::

    $ sudo pip install -r conans/requirements_dev.txt

Running the tests on Ubuntu
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Make sure that the Python requirements have been installed.

Before you can run the tests, you need to set a few environment
variables first.

::

    $ export PYTHONPATH=$PYTHONPATH:$(pwd)

Ensure that your ``cmake`` has version 2.8 or later. You can see the
version with the following command:

::

    $ cmake --version

The appropriate values of ``CONAN_COMPILER`` and
``CONAN_COMPILER_VERSION`` depend on your operating system and your
requirements.

These should work for the GCC from ``build-essential`` on Ubuntu 14.04:

::

    $ export CONAN_COMPILER=gcc
    $ export CONAN_COMPILER_VERSION=4.8

These should work for OS X:

::

    $ export CONAN_COMPILER=clang
    $ export CONAN_COMPILER_VERSION=3.5

Finally, there are some tests that use conan to package Go-lang
libraries, so you would **need to install go-lang** in your computer and
add it to the path.

You can run the actual tests like this:

::

    $ nosetests .

About one minute later it should print ``OK``:

::

    ..................................................................................................................................................
    ----------------------------------------------------------------------
    Ran 146 tests in 50.993s

    OK

Create a launcher
~~~~~~~~~~~~~~~~~

Conan entry point is "conans.conan.main" module. Fill the absolute path
of the cloned repository folder:

::

    #!/usr/bin/env python
    import sys
    sys.path.append('/home/user/conan') # EDIT!!

    from conans.conan import main
    main(sys.argv[1:])

If you are a Windows user, you can name this file "conan.py" and create
a file "conan.bat" that calls the python module:

::

    CALL python C:/Users/user/conan.py %*

Then add that 'conan' file to your PATH and you are ready:

::

    $ conan --help

    Conan commands. Type $conan "command" -h for help
      build      calls your project conanfile.py "build" method.
      export     copies a conanfile.py and associated (export) files to your local store,
      install    install in the local store the given requirements.
      remove     Remove any folder from your local/remote store
      search     show local/remote packages
      test       build and run your package test. Must have conanfile.py with "test"
      upload     uploads a conanfile or binary packages from the local store to any remote.
      user       shows or change the current user 

License
-------

`MIT LICENSE <./LICENSE.md>`__

.. |Build Status1| image:: https://travis-ci.org/conan-io/conan.svg?branch=master
   :target: https://travis-ci.org/conan-io/conan
.. |Build Status2| image:: https://travis-ci.org/conan-io/conan.svg?branch=develop
   :target: https://travis-ci.org/conan-io/conan
.. |Build status3| image:: https://ci.appveyor.com/api/projects/status/5hedgjt9ggj1artx/branch/develop?svg=true
   :target: https://ci.appveyor.com/project/lasote/conan-mva77/branch/master
.. |Build status4| image:: https://ci.appveyor.com/api/projects/status/5hedgjt9ggj1artx/branch/develop?svg=true
   :target: https://ci.appveyor.com/project/lasote/conan-mva77/branch/develop
.. _`pip docs`: https://pip.pypa.io/en/stable/installing/
.. _`brew homepage`: http://brew.sh/

