from conans import ConanFile, CMake, Embedded

class AversivePlusPlusModuleConan(ConanFile):
    name = "AversivePlusPlus"
    version = "0.1"
    settings = "target"
    requires = "base/0.1@AversivePlusPlus/dev", "device-2wheel/0.1@AversivePlusPlus/dev", "feetech/0.1@AversivePlusPlus/dev", "stream/0.1@AversivePlusPlus/dev", "container/0.1@AversivePlusPlus/dev", "device-control/0.1@AversivePlusPlus/dev", "filter/0.1@AversivePlusPlus/dev", "device/0.1@AversivePlusPlus/dev", "toolchain-switch/0.1@AversivePlusPlus/dev"

    def config(self):
        if self.settings.target == "native":
            self.requires("sasiae/0.1@AversivePlusPlus/dev")
        else:
            embed = Embedded(self.settings)
            if self.settings.target == "board":
                if self.settings.target.board in ["arduino_uno", "arduino_mega"]:
                    self.requires("arduino/0.1@AversivePlusPlus/dev")

