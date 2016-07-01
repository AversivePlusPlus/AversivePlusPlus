from conans import ConanFile, CMake, Embedded

class AversivePlusPlusModuleConan(ConanFile):
    name = "AversivePlusPlus"
    version = "0.1"
    exports = "Makefile"
    settings = "target"
    requires = "base/0.1@AversivePlusPlus/dev", "device-2wheel/0.1@AversivePlusPlus/dev", "feetech/0.1@AversivePlusPlus/dev", "hal-switch/0.1@AversivePlusPlus/dev", "memory_mapping/0.1@AversivePlusPlus/dev", "stream/0.1@AversivePlusPlus/dev", "cas/0.1@AversivePlusPlus/dev", "container/0.1@AversivePlusPlus/dev", "device-control/0.1@AversivePlusPlus/dev", "filter/0.1@AversivePlusPlus/dev", "stream-hal/0.1@AversivePlusPlus/dev", "device/0.1@AversivePlusPlus/dev", "device-hal/0.1@AversivePlusPlus/dev", "hal/0.1@AversivePlusPlus/dev", "ik/0.1@AversivePlusPlus/dev", "toolchain-switch/0.1@AversivePlusPlus/dev"

    def config(self):
        embed = Embedded(self.settings)
        if self.settings.target == "board" and self.settings.target.board in ["arduino_uno", "arduino_mega"]:
            self.requires("arduino/0.1@AversivePlusPlus/dev")

