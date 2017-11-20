cmake_minimum_required(VERSION 2.8)

## Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

## Configuration
set(NAME ${CONAN_PACKAGE_NAME})

## Project
project(${NAME} CXX C ASM)
conan_basic_setup()

## Lib sources
file(GLOB_RECURSE SOURCE_CPP "src/*.cpp")
file(GLOB_RECURSE SOURCE_HPP "src/*.hpp")
file(GLOB_RECURSE SOURCE_C "src/*.c")
file(GLOB_RECURSE SOURCE_H "src/*.h")
file(GLOB_RECURSE SOURCE_S "src/*.s")

set(SOURCE
  ${SOURCE_CPP}
  ${SOURCE_HPP}
  ${SOURCE_C}
  ${SOURCE_H}
  ${SOURCE_S}
  )

# Flags
include_directories("include")

# lib
add_library(${NAME} STATIC ${SOURCE})
