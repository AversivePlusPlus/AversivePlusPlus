from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "sasiae"
    version = "0.1"
    exports = "*"

    settings = "os", "compiler", "build_type", "arch", "target"
    requires = "container/0.1@AversivePlusPlus/dev", "device/0.1@AversivePlusPlus/dev", "stream/0.1@AversivePlusPlus/dev", "qt5/0.1@AversivePlusPlus/dev"
    generators = "cmake"

    def build(self):
      cmake = CMake(self.settings)
      self.run('cmake "%s" %s' % (self.conanfile_directory, cmake.command_line))
      self.run('cmake --build . %s' % cmake.build_config)

    def package(self):
      self.copy("*.hpp", src="include", dst="include")
      self.copy("*.h", src="include", dst="include")
      self.copy("*.a", src="lib", dst="lib")

    def package_info(self):
        self.cpp_info.libs += ["sasiae"]
