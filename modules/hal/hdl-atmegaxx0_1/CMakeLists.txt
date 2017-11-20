cmake_minimum_required(VERSION 2.8)

## Conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

## Configuration
set(NAME ${CONAN_PACKAGE_NAME})

## Project
project(${NAME} CXX C ASM)
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

# Startup sources
file(GLOB_RECURSE STARTUP_CPP "startup/*.cpp")
file(GLOB_RECURSE STARTUP_HPP "startup/*.hpp")
file(GLOB_RECURSE STARTUP_C "startup/*.c")
file(GLOB_RECURSE STARTUP_H "startup/*.h")
file(GLOB_RECURSE STARTUP_S "startup/*.s")

set(STARTUP
  ${STARTUP_CPP}
  ${STARTUP_HPP}
  ${STARTUP_C}
  ${STARTUP_H}
  ${STARTUP_S}
  )

# Flags
include_directories("include")

# lib
if(SOURCE)
  add_library(${NAME} STATIC ${SOURCE})
endif()

## Startup lib
if(STARTUP)
  add_library(${NAME}_startup STATIC ${STARTUP})
endif()

# Interface lib
add_custom_target(${NAME}_interface ALL SOURCES ${INTERFACE})

