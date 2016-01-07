cmake_minimum_required(VERSION 2.6)

set(GENERIC_FLAGS "-Wall -Wextra")

set(CMAKE_C_FLAGS   "-std=c11 ${GENERIC_FLAGS}")
set(CMAKE_CXX_FLAGS "-std=c++11 ${GENERIC_FLAGS}")
set(CMAKE_ASM_FLAGS "${GENERIC_FLAGS}")

unset(GENERIC_FLAGS)
