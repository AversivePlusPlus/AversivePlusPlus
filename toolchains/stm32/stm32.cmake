cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0011 NEW)

set(CMAKE_SYSTEM_NAME Generic)

set(AVERSIVE_TOOLCHAIN_STM32 1 CACHE STRING "")

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/generic.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/generic.cmake")
else()
  message(WARNING "Generic toolchain file not found, this toolchain may not work properly.")
endif()

set(STM32_FLAGS "")
set(STM32_FLAGS "${STM32_FLAGS} -DAVERSIVE_TOOLCHAIN_ARM")
set(STM32_FLAGS "${STM32_FLAGS} -DAVERSIVE_TOOLCHAIN_STM32")
set(STM32_FLAGS "${STM32_FLAGS} -DAVERSIVE_TOOLCHAIN_CORTEXM")

set(CMAKE_C_COMPILER     arm-none-eabi-gcc)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${STM32_FLAGS}")

set(CMAKE_CXX_COMPILER   arm-none-eabi-g++)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${STM32_FLAGS}")

set(CMAKE_ASM_COMPILER   arm-none-eabi-gcc)
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${STM32_FLAGS}")

unset(STM32_FLAGS)
