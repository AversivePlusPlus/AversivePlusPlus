from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "stream-riot"
    version = "0.1"
    exports = "*.hpp"
    requires = (
    "riot/0.1@AversivePlusPlus/dev",
    "stream/0.1@AversivePlusPlus/dev",
    )

    def package(self):
        self.copy("*.hpp", src="include", dst="include")

    def package_info(self):
        self.cpp_info.libdirs = []
