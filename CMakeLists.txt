cmake_minimum_required(VERSION 2.6)

project(Aversive++ CXX C ASM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/AversivePlusPlus")

set(subdirs
  base
  memory_mapping
  container
  hal
  hdl-atmegaxx0_1
  hal-stm32cubef4
  stream
  stream-hal
  )

foreach(d ${subdirs})
  add_subdirectory(${d})
endforeach()

set(submodules ${subdirs})
foreach(m ${submodules})
  get_target_property(m_sub ${m} INTERFACE_LINK_LIBRARIES)
  if(m_sub)
    set(submodules ${submodules} ${m_sub})
  endif()
endforeach()
list(REMOVE_DUPLICATES submodules)

set(objs)
foreach(m ${submodules})
  set(objs ${objs} $<TARGET_OBJECTS:${m}_obj>)
endforeach()

set(startup_objs)
foreach(m ${submodules})
  if(TARGET ${m}_startup_obj)
    set(startup_objs ${startup_objs} $<TARGET_OBJECTS:${m}_startup_obj>)
  endif()
endforeach()

add_library(
  Aversive++ STATIC
  ${objs}
  )

add_library(
  startup STATIC
  ${startup_objs}
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
