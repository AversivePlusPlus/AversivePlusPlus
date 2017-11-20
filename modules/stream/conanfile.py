from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "stream"
    version = "0.1"
    exports = "*.hpp"
    requires = "container/0.1@AversivePlusPlus/dev", "device/0.1@AversivePlusPlus/dev"

    def package(self):
      self.copy("*.hpp", src="include", dst="include")
