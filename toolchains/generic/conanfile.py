from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "toolchain-generic"
    version = "0.1"
    exports = "*"

    def package(self):
        self.copy("*.cmake", dst="toolchain")

    def package_info(self):
        self.cpp_info.libdirs = []
