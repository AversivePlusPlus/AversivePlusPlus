cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0011 NEW)

set(AVERSIVE_TOOLCHAIN_TARGET "atmega2560")
include("${CMAKE_CURRENT_LIST_DIR}/atmegaxx0_1.cmake")

set(AVERSIVE_TOOLCHAIN_ATMEGA2560 1 CACHE STRING "")

set(ATMEGA2560_FLAGS "-D__AVR_ATmega2560__")
set(ATMEGA2560_FLAGS "${ATMEGA2560_FLAGS} -DAVERSIVE_TOOLCHAIN_ATMEGA2560")

set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} ${ATMEGA2560_FLAGS}" CACHE STRING "")
set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} ${ATMEGA2560_FLAGS}" CACHE STRING "")
set(CMAKE_ASM_FLAGS    "${CMAKE_ASM_FLAGS} ${ATMEGA2560_FLAGS}" CACHE STRING "")

unset(ATMEGA2560_FLAGS)