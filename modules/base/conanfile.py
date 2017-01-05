from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "base"
    version = "0.1"
    exports = "*.hpp"

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
