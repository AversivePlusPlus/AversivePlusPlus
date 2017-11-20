cmake_minimum_required(VERSION 3.0)

## Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

## Configuration
set(NAME ${CONAN_PACKAGE_NAME})

## Project
project(${NAME} CXX C ASM)
set(CMAKE_CXX_STANDARD 11)
conan_basic_setup()

## Interface
file(GLOB_RECURSE INTERFACE_HPP "include/*.hpp")
file(GLOB_RECURSE INTERFACE_H "include/*.h")

set(INTERFACE
  ${INTERFACE_HPP}
  ${INTERFACE_H}
  )

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

find_package(Qt5Core REQUIRED)

include_directories(include)
add_library(${NAME} STATIC ${SOURCE})
target_link_libraries(${NAME} Qt5::Core)
