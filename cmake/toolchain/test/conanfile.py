from conans import ConanFile, CMake

class AversivePlusPlusProjectConan(ConanFile):
    name="cmake-toolchain-test"
    version="0.1"
    settings = "os", "compiler", "build_type", "arch", "target"
    requires = "cmake-toolchain/0.1@AversivePlusPlus/dev"
    generators = "cmake"

    def imports(self):
      self.copy("toolchain.cmake")

    def build(self):
        cmake = CMake(self.settings)
        toolchain = '-DCMAKE_TOOLCHAIN_FILE=toolchain.cmake'
        self.run('cmake "%s" %s %s' % (self.conanfile_directory, cmake.command_line, toolchain))
        self.run('cmake --build . %s' % cmake.build_config)
