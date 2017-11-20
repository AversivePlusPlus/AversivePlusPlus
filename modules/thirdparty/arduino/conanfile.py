from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "arduino"
    version = "0.1"
    exports = "*"
    settings = "target"

    def build(self):
        sources = '%s/cores/arduino/*.c %s/cores/arduino/*.cpp' % (self.conanfile_directory, self.conanfile_directory)
        inc_arduino = '-I%s/cores/arduino/' % (self.conanfile_directory)
        inc_variant = '-I%s/variants/mega/' % (self.conanfile_directory)
        flags = '-mmcu=atmega2560 -DF_CPU=16000000L -Os'

        if self.settings.target == "arduino-uno":
            inc_variant = '-I%s/variants/standard/' % (self.conanfile_directory)
            flags = '-mmcu=atmega328p -DF_CPU=16000000L -Os'
        elif self.settings.target == "arduino-mega2560":
            inc_variant = '-I%s/variants/mega/' % (self.conanfile_directory)
            flags = '-mmcu=atmega2560 -DF_CPU=16000000L -Os'
            
        self.run('avr-gcc -c %s %s %s %s' % (sources, inc_arduino, inc_variant, flags))
        self.run('avr-ar r libarduino.a *.o')

    def package(self):
      self.copy("*.h", src="cores/arduino", dst="include")
      self.copy("*.a", dst="lib")

      if self.settings.target == "arduino-uno":
          self.copy("*.h", src='variants/standard', dst='include')
      elif self.settings.target == "arduino-mega2560":
          self.copy("*.h", src='variants/mega', dst='include')

    def package_info(self):
        self.cpp_info.libs = ["arduino"]
        self.cpp_info.defines = ["F_CPU=16000000L"]
        if self.settings.target == "arduino-uno":
            self.cpp_info.cflags = ["-mmcu=atmega328p", "-Os"]
            self.cpp_info.cppflags = ["-mmcu=atmega328p", "-Os"]
        elif self.settings.target == "arduino-mega2560":
            self.cpp_info.cflags = ["-mmcu=atmega2560", "-Os"]
            self.cpp_info.cppflags = ["-mmcu=atmega2560", "-Os"]

