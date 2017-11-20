cmake_minimum_required(VERSION 2.6)

set(NAME template-project)
project(${NAME} CXX C ASM)

if(NOT AVERSIVE_TOOLCHAIN_TARGET)
  message(FATAL_ERROR "AVERSIVE_TOOLCHAIN_TARGET undefined")
endif()

file(GLOB_RECURSE SOURCE_CPP "src/*.cpp")
file(GLOB_RECURSE SOURCE_HPP "src/*.hpp")
file(GLOB_RECURSE SOURCE_C "src/*.c")
file(GLOB_RECURSE SOURCE_H "src/*.h")
file(GLOB_RECURSE SOURCE_S "src/*.s")

file(GLOB_RECURSE INCLUDE_HPP "include/*.hpp")
file(GLOB_RECURSE INCLUDE_H "include/*.h")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

link_directories("${CONAN_LIB_DIRS}")
include_directories("${CONAN_INCLUDE_DIRS}")

set(SOURCE
  ${SOURCE_CPP}
  ${SOURCE_HPP}
  ${SOURCE_C}
  ${SOURCE_H}
  ${SOURCE_S}

  ${INCLUDE_HPP}
  ${INCLUDE_H}
  )

add_executable(${NAME} ${SOURCE})

if(CONAN_LIBS)
  target_link_libraries(${NAME} ${CONAN_LIBS})
endif()
