cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0011 NEW)

set(AVERSIVE_TOOLCHAIN_TARGET "sasiae" CACHE STRING "")
set(AVERSIVE_PLATFORM    sasiae)
set(AVERSIVE_MCU         sasiae)

include("${CMAKE_CURRENT_LIST_DIR}/simul.cmake")

set(AVERSIVE_TOOLCHAIN_SASIAE 1 CACHE STRING "")

set(SASIAE_FLAGS "-fPIC")
set(SASIAE_FLAGS "${SASIAE_FLAGS} -DAVERSIVE_TOOLCHAIN_SASIAE")

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${SASIAE_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SASIAE_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${SASIAE_FLAGS}")

set(CMAKE_C_FLAGS   CACHE STRING "")
set(CMAKE_CXX_FLAGS CACHE STRING "")
set(CMAKE_ASM_FLAGS CACHE STRING "")

unset(SASIAE_FLAGS)
