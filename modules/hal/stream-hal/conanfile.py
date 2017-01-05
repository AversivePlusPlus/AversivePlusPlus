from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "stream-hal"
    version = "0.1"
    exports = "*.hpp"
    requires = "stream/0.1@AversivePlusPlus/dev", "hal-switch/0.1@AversivePlusPlus/dev"

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
