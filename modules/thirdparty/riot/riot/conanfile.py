from conans import ConanFile
import os
import StringIO

def riot_board(settings):
    if settings.target == "native32":
        return "native"
    return settings.target

class AversivePlusPlusConanModule(ConanFile):
    name = "riot"
    version = "0.1"
    settings = "os", "compiler", "arch", "target"
    options = { "modules" : "ANY" }
    default_options = "modules=\"\""
    exports = "*"
    
    def make(self, rule = "all"):
        tmp = StringIO.StringIO()
        self.run(
            'make -f builder.mk MODULES={m} BOARD={b} {r} -s'.format(
                b = riot_board(self.settings),
                r = rule,
                m = self.options.modules,
            ),
            tmp
        )
        ret = ""
        if os.path.exists("out.txt"):
            with open("out.txt", "r+") as f:
                ret = f.read()
        return ret

    def run_output(self, cmd):
        ret = StringIO.StringIO()
        self.run(cmd, ret)
        ret.seek(0)
        return ret.read()
        
    
    def source(self):
        self.run("git clone ~/RIOT/.git")
        #self.run("git clone https://github.com/RIOT-OS/RIOT.git --depth 1")

    def build2package(self, s):
        return s.replace(os.getcwd(), "{PACKAGE}")

    def build(self):
        self.make()
        with open("CFLAGS.gcc", "w+") as f:
            f.write(self.build2package(self.make("print_CFLAGS")))
        with open("CXXFLAGS.gcc", "w+") as f:
            f.write(self.build2package(self.make("print_CXXFLAGS")))
        with open("LINKFLAGS.gcc", "w+") as f:
            f.write(self.build2package(self.make("print_LINKFLAGS")))
        with open("USEMODULE.gcc", "w+") as f:
            f.write(self.make("print_USEMODULE"))

    def read_package_file(self, fname):
        ret = ""
        with open(os.path.join(self.package_folder, fname), "r") as f:
            ret = f.read().replace("\n"," ").replace("\"", "\\\\\\\"")
        return ret

    def copy_refs(self, f):
        for p in self.read_package_file(f).split(" "):
            p = p.replace("-L", "").replace("{PACKAGE}/", "")
            if os.path.exists(p):
                if os.path.isdir(p):
                    self.copy(p+"/*")
                else:
                    self.copy(p)

    def package(self):
        self.copy("*.gcc")
        self.copy("*.a", dst="lib", src="bin/{}".format(riot_board(self.settings)))
        self.copy_refs("CFLAGS.gcc")
        self.copy_refs("CXXFLAGS.gcc")
        self.copy_refs("LINKFLAGS.gcc")
        for i in self.make("print_INCLUDES").replace("\n", " ").split(" "):
            idir = i.replace("-I"+os.path.join(os.getcwd(), ""), "")
            self.copy("*.h", dst="include", src=idir)
        for u in self.make("print_STARTUP").replace("\n", " ").split(" "):
            self.copy(str(os.path.split(u)[1]), dst="startup", src=str(os.path.split(u)[0]))
        
    def package_info(self):
        self.cpp_info.libdirs = []
        cppflags = self.read_package_file("CXXFLAGS.gcc").format(PACKAGE=self.package_folder).split(" ")
        cflags = self.read_package_file("CFLAGS.gcc").format(PACKAGE=self.package_folder).split(" ")
        lflags = self.read_package_file("LINKFLAGS.gcc").format(PACKAGE=self.package_folder).split(" ")
        mod = self.read_package_file("USEMODULE.gcc").split(" ")
        self.cpp_info.cppflags = cppflags
        self.cpp_info.cflags = cflags
        for u in os.listdir(os.path.join(self.package_folder, "startup")):
            self.cpp_info.exelinkflags += [
                os.path.join(self.package_folder, "startup", u)
            ]
        if self.settings.compiler in ["gcc", "avr-gcc", "arm-none-eabi-gcc"]:
            self.cpp_info.libs += ["-Wl,--start-group"]
            for m in mod:
                path = os.path.join(self.package_folder, "lib", m+".a")
                if os.path.exists(path):
                    self.cpp_info.libs += [
                        path
                    ]
            self.cpp_info.libs += ["-Wl,--end-group"]
        elif self.settings.compiler in ["clang", "apple-clang"] :
            for m in mod:
                path = os.path.join(self.package_folder, "lib", m+".a")
                if os.path.exists(path) and (8 < os.path.getsize(path)):
                    self.cpp_info.libs += [
                        path
                    ]
            self.cpp_info.libs += ["-Wl,-no_pie"]
        self.cpp_info.exelinkflags += lflags
