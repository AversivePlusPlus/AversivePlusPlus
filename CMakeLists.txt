cmake_minimum_required(VERSION 2.6)

project(Aversive++ CXX C ASM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/base")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/memory_mapping")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/hdl/atmegaxx0_1")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/hal")
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/hal-stm32cubef4")

add_library(
  Aversive++ STATIC
  $<TARGET_OBJECTS:base_obj>
  $<TARGET_OBJECTS:memory_mapping_obj>
  $<TARGET_OBJECTS:hdl-atmegaxx0_1_obj>
  $<TARGET_OBJECTS:hal-stm32cubef4_obj>
  )

add_library(
  startup STATIC
  $<TARGET_OBJECTS:hdl-atmegaxx0_1_startup_obj>
  $<TARGET_OBJECTS:hal-stm32cubef4_startup_obj>
  )

set_target_properties(Aversive++ PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(startup PROPERTIES LINKER_LANGUAGE CXX)
