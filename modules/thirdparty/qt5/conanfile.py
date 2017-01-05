from conans import ConanFile, CMake

class AversivePlusPlusModuleConan(ConanFile):
    name = "qt5"
    version = "0.1"

    settings = "os"

    def package_info(self):
        self.cpp_info.cppflags += ["-fPIC"]
        if self.settings.os == "Linux":
            self.cpp_info.libs += ["Qt5Core"]
            self.cpp_info.includedirs += ['/usr/include/qt5']
        elif self.settings.os == "Macos":
            self.cpp_info.exelinkflags += ["-F /usr/local/lib", "-framework QtCore"]
        else:
            raise Exception("OS '%s' not supported!" % (self.settings.os))
