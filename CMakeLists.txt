cmake_minimum_required(VERSION 2.6)

project(Aversive++ CXX C ASM)

if("${AVERSIVE_MCU}" STREQUAL "")
  set(INSTALL_INTERFACE 1)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/AversivePlusPlus")

set(subdirs
  base
  memory_mapping
  container

  cmsis-core
  cmsis-stm32f4xx
  stm32cube-hal-stm32f4xx
  
  hdl-atmegaxx0_1

  hal
  hal-stm32cubef4
  hal-atxmega

  device

  stream
  stream-hal
  )

foreach(d ${subdirs})
  add_subdirectory(modules/${d})
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
  if(TARGET ${m}_obj)
    set(objs ${objs} $<TARGET_OBJECTS:${m}_obj>)
  endif()
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

set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "15")
set(CPACK_PACKAGE_VERSION_MINOR "12")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "gcc-arm-none-eabi,cmake")
set(CPACK_PACKAGE_DESCRIPTION "A C++ API that eases microcontroller programming")
set(CPACK_PACKAGE_CONTACT "Loic Dauphin astralien3000@yahoo.fr")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")

INCLUDE(CPack)
