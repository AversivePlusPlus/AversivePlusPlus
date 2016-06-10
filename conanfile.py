from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "AversivePlusPlus"
    version = "0.1"
    exports = ""
    settings = "target"
    requires = "base/0.1@AversivePlusPlus/stable", "device-2wheel/0.1@AversivePlusPlus/stable", "feetech/0.1@AversivePlusPlus/stable", "hal-switch/0.1@AversivePlusPlus/stable", "memory_mapping/0.1@AversivePlusPlus/stable", "stream/0.1@AversivePlusPlus/stable", "cas/0.1@AversivePlusPlus/stable", "container/0.1@AversivePlusPlus/stable", "device-control/0.1@AversivePlusPlus/stable", "filter/0.1@AversivePlusPlus/stable", "stream-hal/0.1@AversivePlusPlus/stable", "device/0.1@AversivePlusPlus/stable", "device-hal/0.1@AversivePlusPlus/stable", "hal/0.1@AversivePlusPlus/stable", "ik/0.1@AversivePlusPlus/stable", "toolchain-switch/0.1@AversivePlusPlus/stable"

    def config(self):
        if self.settings.target == "sasiae":
            self.requires("sasiae/0.1@AversivePlusPlus/stable")
