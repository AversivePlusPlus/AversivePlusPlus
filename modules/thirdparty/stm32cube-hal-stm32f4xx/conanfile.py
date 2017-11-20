from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "stm32cube-hal-stm32f4xx"
    version = "0.1"
    exports = "*"

    settings = "os", "compiler", "build_type", "arch", "target"
    requires = "cmsis-stm32f4xx/0.1@AversivePlusPlus/dev", "toolchain-switch/0.1@AversivePlusPlus/dev"
    generators = "cmake"

    def imports(self):
      self.copy("*.cmake", dst="toolchain", src="toolchain")
      self.copy("*.ld", dst="toolchain/linker", src="linker")

    def build(self):
      cmake = CMake(self.settings)
      toolchain = '-DCMAKE_TOOLCHAIN_FILE=toolchain/%s.cmake' % self.settings.target
      self.run('cmake "%s" %s %s' % (self.conanfile_directory, cmake.command_line, toolchain))
      self.run('cmake --build . %s' % cmake.build_config)

    def package(self):
      self.copy("*.hpp", src="include", dst="include")
      self.copy("*.h", src="include", dst="include")
      self.copy("*.a", src="lib", dst="lib")
