import sys
import os

def writeln(f, txt):
    f.write(txt+"\n")

def gen_cmake(fx, fxxx, fxxxxx):
    FX = fx
    FXXX = fxxx
    FXXXXX = fxxxxx

    NAME_UP = "STM32F"+FX+FXXX+FXXXXX.upper()
    NAME_LOW = NAME_UP.lower()
    PARENT = "stm32f"+FX+FXXX

    LINKER = None
    for f in os.listdir("linker"):
        if(f[0:11] == NAME_UP):
            LINKER = f

    f = open(NAME_LOW+".cmake", "w")

    writeln(f, 'cmake_minimum_required(VERSION 2.6)')
    writeln(f, 'cmake_policy(SET CMP0011 NEW)')
    writeln(f, '')
    writeln(f, 'set(AVERSIVE_TOOLCHAIN_TARGET "'+NAME_LOW+'" CACHE STRING "")')
    writeln(f, 'set(AVERSIVE_TOOLCHAIN_'+NAME_UP+' 1 CACHE STRING "")')
    writeln(f, 'include("${CMAKE_CURRENT_LIST_DIR}/'+PARENT+'.cmake")')
    writeln(f, '')
    writeln(f, 'set('+NAME_UP+'_FLAGS "-DAVERSIVE_TOOLCHAIN_'+NAME_UP+'")')
    writeln(f, 'set('+NAME_UP+'_LINKER_FLAGS "-T${CMAKE_CURRENT_LIST_DIR}/linker/'+LINKER+' --specs=nosys.specs")')
    writeln(f, '')
    writeln(f, 'set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} ${'+NAME_UP+'_FLAGS}" CACHE STRING "")')
    writeln(f, 'set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} ${'+NAME_UP+'_FLAGS}" CACHE STRING "")')
    writeln(f, 'set(CMAKE_ASM_FLAGS    "${CMAKE_ASM_FLAGS} ${'+NAME_UP+'_FLAGS}" CACHE STRING "")')
    writeln(f, '')
    writeln(f, 'set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${'+NAME_UP+'_LINKER_FLAGS}" CACHE STRING "")')
    writeln(f, '')
    writeln(f, 'unset('+NAME_UP+'_FLAGS)')
