from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "device-2wheel"
    version = "0.1"
    exports = "*.hpp"
    requires = "base/0.1@AversivePlusPlus/dev", "device/0.1@AversivePlusPlus/dev"

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
