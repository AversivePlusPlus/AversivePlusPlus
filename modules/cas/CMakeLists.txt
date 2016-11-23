cmake_minimum_required(VERSION 2.8)

## User configuration
include(module.cmake)

## Project

project(${NAME} CXX C ASM)

## Dependencies check

set(DEP_OK 1)
foreach(dep IN ITEMS ${DEPENDENCIES})
  if(NOT TARGET ${dep})
    message(WARNING "Missing dependency : ${dep}")
    set(DEP_OK 0)
  endif()
endforeach()
if(NOT ${DEP_OK})
  message(FATAL_ERROR "Can't compile if dependencies are missing")
endif()

## Interface

file(GLOB_RECURSE INTERFACE_HPP "include/*.hpp")
file(GLOB_RECURSE INTERFACE_H "include/*.h")

if(COMPILE_LIB)
  ## Regular lib

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

  if(SOURCE)
    add_library(
      ${NAME}_obj OBJECT
      ${SOURCE}
      )
    target_include_directories(${NAME}_obj PUBLIC "include")
    foreach(dep IN ITEMS ${DEPENDENCIES})
      get_target_property(INCLUDE_PATH ${dep} INTERFACE_INCLUDE_DIRECTORIES)
      target_include_directories(${NAME}_obj PUBLIC ${INCLUDE_PATH})
    endforeach(dep)
  endif()

  ## Startup lib
  if(STARTUP)
    add_library(
      ${NAME}_startup_obj OBJECT
      ${STARTUP}
      )
    target_include_directories(${NAME}_startup_obj PUBLIC "include")
    foreach(dep IN ITEMS ${DEPENDENCIES})
      get_target_property(INCLUDE_PATH ${dep} INTERFACE_INCLUDE_DIRECTORIES)
      target_include_directories(${NAME}_startup_obj PUBLIC ${INCLUDE_PATH})
    endforeach(dep)
  endif()
endif()

# Interface lib

add_library(
  ${NAME} STATIC
  ${INTERFACE_HPP}
  ${INTERFACE_H}
  )

target_include_directories(${NAME} PUBLIC "include")
foreach(dep IN ITEMS ${DEPENDENCIES})
  get_target_property(INCLUDE_PATH ${dep} INTERFACE_INCLUDE_DIRECTORIES)
  target_include_directories(${NAME} PUBLIC ${INCLUDE_PATH})
  target_link_libraries(${NAME} PUBLIC ${dep})
endforeach(dep)

set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE CXX)

## Install
if(INSTALL_INTERFACE)
  if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
    install(DIRECTORY
      include
      DESTINATION .
      )
  endif()
endif()