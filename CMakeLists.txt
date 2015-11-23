cmake_minimum_required(VERSION 2.6)

project(Aversive++ CXX C ASM)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/base")

add_library(Aversive++ STATIC $<TARGET_OBJECTS:base_obj>)

set_target_properties(Aversive++ PROPERTIES LINKER_LANGUAGE CXX)