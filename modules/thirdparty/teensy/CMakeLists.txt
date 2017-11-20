cmake_minimum_required(VERSION 3.1)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

set(NAME ${CONAN_PACKAGE_NAME})
project(${NAME} CXX C)

conan_basic_setup()

file(GLOB_RECURSE SOURCE_CPP "cores/teensy3/*.cpp")
file(GLOB_RECURSE SOURCE_HPP "cores/teensy3/*.hpp")
file(GLOB_RECURSE SOURCE_C "cores/teensy3/*.c")
file(GLOB_RECURSE SOURCE_H "cores/teensy3/*.h")

set(SOURCE
  ${SOURCE_CPP}
  ${SOURCE_HPP}
  ${SOURCE_C}
  ${SOURCE_H}
  )

include_directories("cores/teensy3")

add_definitions(-DF_CPU=48000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE)
add_definitions(-D__MK20DX256__ -DARDUINO=10613 -DTEENSYDUINO=132)

set(ALL_FLAGS "-Wall -g -Os")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ALL_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -felide-constructors -fno-exceptions -fno-rtti")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ALL_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${ALL_FLAGS}")

add_library(${NAME} STATIC ${SOURCE})
