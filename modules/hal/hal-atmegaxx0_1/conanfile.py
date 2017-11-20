from conans import ConanFile, CMake, Embedded

class AversivePlusPlusModuleConan(ConanFile):
    name = "hal-atmegaxx0_1"
    version = "0.1"
    exports = "*"

    settings = "os", "compiler", "build_type", "arch", "target"
    requires = "hal/0.1@AversivePlusPlus/dev", "hdl-atmegaxx0_1/0.1@AversivePlusPlus/dev", "toolchain-switch/0.1@AversivePlusPlus/dev"
    generators = "cmake"

    def imports(self):
        self.copy("*.cmake", dst="toolchain", src="toolchain")
        self.copy("*.ld", dst="toolchain/linker", src="linker")

    def build(self):
        cmake = CMake(self.settings)
        embed = Embedded(self.settings)
        toolchain = '-DCMAKE_TOOLCHAIN_FILE=toolchain/%s.cmake' % embed.microcontroller()
        self.run('cmake "%s" %s %s' % (self.conanfile_directory, cmake.command_line, toolchain))
        self.run('cmake --build . %s' % cmake.build_config)

    def package(self):
        self.copy("*.hpp", src="include", dst="include")
        self.copy("*.h", src="include", dst="include")
        self.copy("*.a", src="lib", dst="lib")

    def package_info(self):
        self.cpp_info.libs += ["hal-atmegaxx0_1"]
