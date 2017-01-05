cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0011 NEW)

set(CMAKE_SYSTEM_NAME Generic)

set(AVERSIVE_TOOLCHAIN_AVR 1 CACHE STRING "")

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/generic.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/generic.cmake")
else()
  message(WARNING "Generic toolchain file not found, this toolchain may not work properly.")
endif()
  
set(AVR_FLAGS "-Os -mcall-prologues -I${CMAKE_CURRENT_SOURCE_DIR}/include/avr -mmcu=${AVERSIVE_TOOLCHAIN_TARGET}")
set(AVR_FLAGS "${AVR_FLAGS} -DAVERSIVE_TOOLCHAIN_AVR")

set(AVERSIVE_PLATFORM    avr)

set(CMAKE_C_COMPILER     avr-gcc)
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${AVR_FLAGS}")

set(CMAKE_CXX_COMPILER   avr-g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${AVR_FLAGS} -fno-rtti -fno-exceptions")

set(CMAKE_ASM_COMPILER   avr-gcc)
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${AVR_FLAGS}")

unset(AVR_FLAGS)
