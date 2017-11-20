from conans import ConanFile, CMake, Embedded
import sys
import os

def writeln(f, txt):
    f.write(txt+"\n")

def gen_cmake(embed):
    f = open("toolchain.cmake", "w")

    writeln(f, 'cmake_minimum_required(VERSION 2.6)')
    writeln(f, 'cmake_policy(SET CMP0011 NEW)')
    writeln(f, '')
    if (not "native" in embed.groups()) and (not "native" in embed.groups()):
        writeln(f, 'set(CMAKE_SYSTEM_NAME Generic)')
        writeln(f, '')
    if "cortex_m" in embed.groups():
        writeln(f, 'set(CMAKE_C_COMPILER arm-none-eabi-gcc)')
        writeln(f, 'set(CMAKE_C_COMPILER_WORKS 1)')
        writeln(f, 'set(CMAKE_CXX_COMPILER arm-none-eabi-g++)')
        writeln(f, 'set(CMAKE_CXX_COMPILER_WORKS 1)')
        writeln(f, 'set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)')
    if "avr" in embed.groups():
        writeln(f, 'set(CMAKE_C_COMPILER avr-gcc)')
        writeln(f, 'set(CMAKE_C_COMPILER_WORKS 1)')
        writeln(f, 'set(CMAKE_CXX_COMPILER avr-g++)')
        writeln(f, 'set(CMAKE_CXX_COMPILER_WORKS 1)')
        writeln(f, 'set(CMAKE_ASM_COMPILER avr-gcc)')
    writeln(f, '')
    writeln(f, 'set(ALL_FLAGS "")')
    if "avr" in embed.groups():
        writeln(f, 'set(ALL_FLAGS "${ALL_FLAGS} -mmcu='+embed.microcontroller()+'")')
    if "cortex_m0" in embed.groups():
        writeln(f, 'set(ALL_FLAGS "${ALL_FLAGS} -mcpu=cortex-m0")')
    if "cortex_m0plus" in embed.groups():
        writeln(f, 'set(ALL_FLAGS "${ALL_FLAGS} -mcpu=cortex-m0plus")')
    if "cortex_m4" in embed.groups():
        writeln(f, 'set(ALL_FLAGS "${ALL_FLAGS} -mcpu=cortex-m4")')
    if "cortex_m" in embed.groups():
        writeln(f, 'set(ALL_FLAGS "${ALL_FLAGS} -mthumb")')
    writeln(f, '')
    writeln(f, 'set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${ALL_FLAGS}")')
    writeln(f, '')
    writeln(f, 'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ALL_FLAGS}")')
    writeln(f, 'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")')
    writeln(f, 'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")')
    writeln(f, 'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-threadsafe-statics")')
    writeln(f, '')
    writeln(f, 'set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${ALL_FLAGS}")')
    writeln(f, '')
    writeln(f, 'unset(ALL_FLAGS)')
    writeln(f, '')
    writeln(f, 'set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "")')
    writeln(f, 'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "")')
    writeln(f, 'set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS}" CACHE STRING "")')
    writeln(f, '')

class AversivePlusPlusModuleConan(ConanFile):
    name = "cmake-toolchain"
    version = "0.1"
    settings = "os", "compiler", "build_type", "arch", "target"

    def build(self):
        embed = Embedded(self.settings)
        gen_cmake(embed)

    def package(self):
        self.copy("toolchain.cmake")

    def package_info(self):
        self.cpp_info.libdirs = ["test"]
        self.env_info.test = "test"
