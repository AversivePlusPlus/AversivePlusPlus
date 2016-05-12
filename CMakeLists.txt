cmake_minimum_required(VERSION 3.2)

project(Aversive++ CXX C ASM)

if(NOT CMAKE_TOOLCHAIN_FILE)
  set(INSTALL_INTERFACE 1)
  set(INSTALL_TOOLCHAINS 1)
else()
  if(NOT AVERSIVE_TOOLCHAIN_TARGET)
    message(FATAL_ERROR "AVERSIVE_TOOLCHAIN_TARGET undefined")
  endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/AversivePlusPlus")

set(subdirs
  base
  memory_mapping
  container

  cas
  ik

  cmsis-core
  cmsis-stm32f4xx
  stm32cube-hal-stm32f4xx

  hdl-atmegaxx0_1

  hal
  hal-stm32cubef4
  hal-atxmega
  hal-atmegaxx0_1
  hal-switch

  filter

  device
  device-hal
  device-control
  device-2wheel

  stream
  stream-hal

  feetech

  sasiae
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
  ARCHIVE DESTINATION lib/${AVERSIVE_TOOLCHAIN_TARGET}
  )

if(INSTALL_TOOLCHAINS)
install(DIRECTORY
  toolchain
  DESTINATION .
  )
endif()

set(CPACK_GENERATOR DEB RPM NSIS)
set(CPACK_PACKAGE_VERSION "16.03")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "cmake,gcc-arm-none-eabi,gcc-avr,avr-libc,g++,qt5-default")
set(CPACK_PACKAGE_DESCRIPTION "A C++ API that eases microcontroller programming")
set(CPACK_PACKAGE_CONTACT "Loic Dauphin astralien3000@yahoo.fr")
set(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
#set(CPACK_DEB_COMPONENT_INSTALL ON)
#set(CPACK_RPM_COMPONENT_INSTALL ON)

if(NOT AVERSIVE_TOOLCHAIN_TARGET)
  set(CPACK_PACKAGE_NAME "aversive++")
else()
  set(CPACK_PACKAGE_NAME "aversive++-${AVERSIVE_TOOLCHAIN_TARGET}")
endif()

INCLUDE(CPack)
