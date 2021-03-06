cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0011 NEW)

set(AVERSIVE_TOOLCHAIN_TARGET "stm32f479ni" CACHE STRING "")
set(AVERSIVE_TOOLCHAIN_STM32F479NI 1 CACHE STRING "")
include("${CMAKE_CURRENT_LIST_DIR}/stm32f479.cmake")

set(STM32F479NI_FLAGS "-DAVERSIVE_TOOLCHAIN_STM32F479NI")
set(STM32F479NI_LINKER_FLAGS "-T${CMAKE_CURRENT_LIST_DIR}/linker/STM32F479NIHx_FLASH.ld --specs=nosys.specs")

set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} ${STM32F479NI_FLAGS}" CACHE STRING "")
set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} ${STM32F479NI_FLAGS}" CACHE STRING "")
set(CMAKE_ASM_FLAGS    "${CMAKE_ASM_FLAGS} ${STM32F479NI_FLAGS}" CACHE STRING "")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${STM32F479NI_LINKER_FLAGS}" CACHE STRING "")

unset(STM32F479NI_FLAGS)
