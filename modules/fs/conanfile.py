from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "fs"
    version = "0.1"
    exports = "*"
    requires = "container/0.1@AversivePlusPlus/dev", "stream/0.1@AversivePlusPlus/dev"
    generators = "cmake"

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
        self.copy("*.h", src="include", dst="include")

    def package_info(self):
        self.cpp_info.libs += []
