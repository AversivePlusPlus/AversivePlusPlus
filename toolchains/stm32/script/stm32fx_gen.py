import sys
import os

def writeln(f, txt):
    f.write(txt+"\n")

def gen_cmake(fx):
    FX = fx

    NAME_UP = "STM32F"+FX
    NAME_LOW = NAME_UP.lower()

    f = open(NAME_LOW+".cmake", "w")

    writeln(f, 'cmake_minimum_required(VERSION 2.6)')
    writeln(f, 'cmake_policy(SET CMP0011 NEW)')
    writeln(f, '')
    writeln(f, 'set(AVERSIVE_TOOLCHAIN_'+NAME_UP+' 1 CACHE STRING "")')
    writeln(f, 'set(AVERSIVE_TOOLCHAIN_CORTEXM4 1 CACHE STRING "")')
    writeln(f, '')
    writeln(f, 'include("${CMAKE_CURRENT_LIST_DIR}/stm32.cmake")')
    writeln(f, '')
    writeln(f, 'set(STM32F4_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -Wdouble-promotion -ffunction-sections -fdata-sections -DSTM32F40_41xxx -DDEBUG -DUSART_DEBUG=USART1 -DHSE_VALUE=8000000")')
    writeln(f, 'set(STM32F4_FLAGS "${STM32F4_FLAGS} -DAVERSIVE_TOOLCHAIN_'+NAME_UP+'")')
    writeln(f, 'set(STM32F4_FLAGS "${STM32F4_FLAGS} -DAVERSIVE_TOOLCHAIN_CORTEXM4")')
    writeln(f, '')
    writeln(f, 'set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${STM32F4_FLAGS}")')
    writeln(f, 'set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STM32F4_FLAGS} -fno-rtti -fno-exceptions -fno-threadsafe-statics")')
    writeln(f, 'set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${STM32F4_FLAGS}")')
    writeln(f, '')
    writeln(f, 'unset(STM32F4_FLAGS)')
