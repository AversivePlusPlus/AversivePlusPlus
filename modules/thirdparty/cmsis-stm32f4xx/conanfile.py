from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "cmsis-stm32f4xx"
    version = "0.1"
    exports = "*"
    requires = "cmsis-core/0.1@AversivePlusPlus/dev"

    def package(self):
        self.copy("*.h", src="include", dst="include")
