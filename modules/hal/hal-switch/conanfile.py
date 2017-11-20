from conans import ConanFile, CMake, Embedded

class AversivePlusPlusModuleConan(ConanFile):
    name = "hal-switch"
    version = "0.1"
    exports = "*"
    settings = "os", "compiler", "build_type", "arch", "target"

    def config(self):
        embed = Embedded(self.settings)
        if "stm32f4" in embed.groups():
            self.requires("hal-stm32cubef4/0.1@AversivePlusPlus/dev")
        if "atmegaxx0_1" in embed.groups():
            self.requires("hal-atmegaxx0_1/0.1@AversivePlusPlus/dev")

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
