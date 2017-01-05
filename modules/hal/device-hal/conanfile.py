from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "device-hal"
    version = "0.1"
    exports = "*.hpp"
    requires = "device/0.1@AversivePlusPlus/dev", "hal-switch/0.1@AversivePlusPlus/dev"

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
