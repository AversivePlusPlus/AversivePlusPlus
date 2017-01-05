import sys
import os

def writeln(f, txt):
    f.write(txt+"\n")

def gen_cmake(fx, fxxx):
    FX = fx
    FXXX = fxxx

    NAME_UP = "STM32F"+FX+FXXX
    NAME_LOW = NAME_UP.lower()

    STARTUP = None
    for f in os.listdir("../../modules/cmsis-stm32f4xx/startup"):
        S = f.replace("startup_","").replace(".s","")
        if(S[0:9] == "stm32f"+FX+FXXX):
            STARTUP = S

    END_LOW = STARTUP[9:]
    END_UP = END_LOW.upper().replace("X", "x")

    INC = "stm32f"+FX
    MCU = "stm32f"+FX+FXXX+END_LOW
    DEF = "STM32F"+FX+FXXX+END_UP
    FLAG = "STM32F"+FX+FXXX+"XX"

    f = open(NAME_LOW+".cmake", "w")

    writeln(f, "cmake_minimum_required(VERSION 2.6)")
    writeln(f, "cmake_policy(SET CMP0011 NEW)")
    writeln(f, "")
    writeln(f, 'set(AVERSIVE_TOOLCHAIN_'+NAME_UP+' 1 CACHE STRING "")')
    writeln(f, 'set(AVERSIVE_TOOLCHAIN_MCU "'+MCU+'" CACHE STRING "")')
    writeln(f, 'include("${CMAKE_CURRENT_LIST_DIR}/'+INC+'.cmake")')
    writeln(f, "")
    writeln(f, 'set('+FLAG+'_FLAGS "-D'+DEF+' -s")')
    writeln(f, 'set('+FLAG+'_FLAGS "${'+FLAG+'_FLAGS} -DAVERSIVE_TOOLCHAIN_'+NAME_UP+'")')
    writeln(f, "")
    writeln(f, 'set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} ${'+FLAG+'_FLAGS}")')
    writeln(f, 'set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} ${'+FLAG+'_FLAGS}")')
    writeln(f, 'set(CMAKE_ASM_FLAGS    "${CMAKE_ASM_FLAGS} ${'+FLAG+'_FLAGS}")')
    writeln(f, '')
    writeln(f, 'unset('+FLAG+'_FLAGS)')
