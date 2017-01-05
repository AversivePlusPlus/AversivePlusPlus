cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0011 NEW)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/generic.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/generic.cmake")
else()
  message(WARNING "Generic toolchain file not found, this toolchain may not work properly.")
endif()

set(AVERSIVE_TOOLCHAIN_SIMUL 1 CACHE STRING "")

set(SIMUL_FLAGS "-Os")
set(SIMUL_FLAGS "${SIMUL_FLAGS} -DAVERSIVE_TOOLCHAIN_SIMUL")

set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${SIMUL_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SIMUL_FLAGS}")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${SIMUL_FLAGS}")

unset(SIMUL_FLAGS)
