from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "toolchain-switch"
    requires= "toolchain-avr/0.1@AversivePlusPlus/dev", "toolchain-simul/0.1@AversivePlusPlus/dev", "toolchain-stm32/0.1@AversivePlusPlus/dev"
    version = "0.1"
    exports = "*"

    def package(self):
        self.copy("*.cmake", dst="toolchain")

    def package_info(self):
        self.cpp_info.libdirs = []
