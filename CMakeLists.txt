cmake_minimum_required(VERSION 2.8)

project(Aversive++ CXX C ASM)

file(GLOB_RECURSE SOURCE_CPP "modules/*.cpp")
file(GLOB_RECURSE SOURCE_HPP "modules/*.hpp")
file(GLOB_RECURSE SOURCE_C "modules/*.c")
file(GLOB_RECURSE SOURCE_H "modules/*.h")
file(GLOB_RECURSE SOURCE_S "modules/*.h")

file(GLOB_RECURSE MODULES_CMAKELISTS "modules/*/CMakeLists.txt")
file(GLOB_RECURSE MODULES_CMAKE "modules/*/module.cmake")
file(GLOB_RECURSE CONANFILES "*/conanfile.py")

file(GLOB_RECURSE TOOLCHAINS "toolchain/*.cmake")

add_custom_target(dummy ALL SOURCES
  ${SOURCE_CPP}
  ${SOURCE_HPP}
  ${SOURCE_C}
  ${SOURCE_H}
  ${SOURCE_S}
  ${MODULES_CMAKELISTS}
  ${MODULES_CMAKE}
  ${CONANFILES}
  ${TOOLCHAINS}
  )
