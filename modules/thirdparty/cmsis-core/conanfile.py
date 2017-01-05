from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "cmsis-core"
    version = "0.1"
    exports = "*"

    def package(self):
        self.copy("*.h", src="include", dst="include")
