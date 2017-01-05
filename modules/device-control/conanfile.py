from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "device-control"
    version = "0.1"
    exports = "*.hpp"
    requires = "device/0.1@AversivePlusPlus/dev", "filter/0.1@AversivePlusPlus/dev"

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
