cmake_minimum_required(VERSION 2.6)

project(Aversive++ CXX C ASM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/AversivePlusPlus")

add_subdirectory("base")
add_subdirectory("memory_mapping")
add_subdirectory("container")
add_subdirectory("hal")

add_subdirectory("hdl-atmegaxx0_1")
add_subdirectory("hal-stm32cubef4")

add_subdirectory("stream")
add_subdirectory("stream-hal")


add_library(
  Aversive++ STATIC
  $<TARGET_OBJECTS:base_obj>
  $<TARGET_OBJECTS:memory_mapping_obj>
  $<TARGET_OBJECTS:hdl-atmegaxx0_1_obj>
  $<TARGET_OBJECTS:hal-stm32cubef4_obj>
  $<TARGET_OBJECTS:stm32cube-hal-stm32f4xx_obj>
  $<TARGET_OBJECTS:cmsis-stm32f4xx_obj>
  $<TARGET_OBJECTS:stream_obj>
  )

add_library(
  startup STATIC
  $<TARGET_OBJECTS:hdl-atmegaxx0_1_startup_obj>
  $<TARGET_OBJECTS:hal-stm32cubef4_startup_obj>
  $<TARGET_OBJECTS:cmsis-stm32f4xx_startup_obj>
  $<TARGET_OBJECTS:stm32cube-hal-stm32f4xx_startup_obj>
  )

set_target_properties(Aversive++ PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(startup PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS
  Aversive++ startup
  ARCHIVE DESTINATION lib/${AVERSIVE_MCU}
  )

install(DIRECTORY
  cmake/toolchain
  DESTINATION .
  )

SET(CPACK_GENERATOR "DEB;RPM")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "astralien3000")
SET(CPACK_PACKAGE_VERSION "15.xx")

INCLUDE(CPack)
