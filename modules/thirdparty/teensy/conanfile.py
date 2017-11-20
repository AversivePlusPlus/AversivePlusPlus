from conans import ConanFile, CMake

class AversivePlusPlusConanModule(ConanFile):
    name = "teensy"
    version = "0.1"
    exports = "CMakeLists.txt"
    settings = "os", "compiler", "arch", "target"
    requires = "cmake-toolchain/0.1@AversivePlusPlus/dev"
    generators = "cmake"

    def imports(self):
        self.copy("toolchain.cmake")

    def source(self):
        self.run("git clone https://github.com/PaulStoffregen/cores.git --depth 1")

    def build(self):
        cmake = CMake(self.settings)
        toolchain = '-DCMAKE_TOOLCHAIN_FILE=toolchain.cmake'
        self.run('cmake "%s" %s %s' % (self.conanfile_directory, cmake.command_line, toolchain))
        self.run('cmake --build . %s' % cmake.build_config)

    def package(self):
        self.copy("*.hpp", src="cores/teensy3", dst="include")
        self.copy("*.h", src="cores/teensy3", dst="include")
        self.copy("*.a", src="lib", dst="lib")
        self.copy("mk20dx256.ld", src="cores/teensy3", dst="linker")

    def package_info(self):
        self.cpp_info.libs = ["teensy"]
        self.cpp_info.defines += ["F_CPU=48000000", "USB_SERIAL", "LAYOUT_US_ENGLISH", "USING_MAKEFILE"]
        self.cpp_info.defines += ["__MK20DX256__", "ARDUINO=10613", "TEENSYDUINO=132"]
        self.cpp_info.cflags += ["-Wall", "-g", "-Os"]
        self.cpp_info.cppflags += ["-Wall", "-g", "-Os", "-std=gnu++0x", "-felide-constructors", "-fno-exceptions", "-fno-rtti"]
        self.cpp_info.exelinkflags += ["-Wl,--gc-sections,--defsym=__rtc_localtime=0", "--specs=nano.specs"]
        self.cpp_info.exelinkflags += ["-T{}/linker/mk20dx256.ld".format(self.package_folder)]
