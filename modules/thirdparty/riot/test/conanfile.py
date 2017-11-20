from conans import ConanFile, CMake, Embedded

class AversivePlusPlusProjectConan(ConanFile):
    name="riot-test"
    version="0.1"
    settings = "os", "compiler", "build_type", "arch", "target"
    requires = (
        "stream-riot/0.1@AversivePlusPlus/dev",
        "toolchain-switch/0.1@AversivePlusPlus/dev",
        )
    default_options = "riot:modules=\"shell shell_commands\""
    generators = "cmake", "txt"

    def imports(self):
        self.copy("*.cmake", dst="toolchain", src="toolchain")
        self.copy("*.ld", dst="toolchain/linker", src="linker")

    def build(self):
        cmake = CMake(self.settings)
        toolchain = ""
        if self.settings.target == "native":
            toolchain = '-DCMAKE_TOOLCHAIN_FILE=toolchain/%s.cmake' % "native32"
        elif self.settings.target == "arduino-mega2560":
            toolchain = '-DCMAKE_TOOLCHAIN_FILE=toolchain/%s.cmake' % "atmega2560"
        elif self.settings.target == "samr21-xpro":
            toolchain = " ".join([
                "-DCMAKE_SYSTEM_NAME=Generic",
                "-DCMAKE_C_COMPILER=arm-none-eabi-gcc",
                "-DCMAKE_CXX_COMPILER=arm-none-eabi-g++",
                "-DCMAKE_C_FLAGS=--specs=nosys.specs",
                "-DCMAKE_CXX_FLAGS=--specs=nosys.specs",
            ])

        self.run('cmake "%s" %s %s' % (self.conanfile_directory, cmake.command_line, toolchain))
        self.run('cmake --build . %s' % cmake.build_config)
