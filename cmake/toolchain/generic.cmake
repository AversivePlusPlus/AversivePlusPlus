cmake_minimum_required(VERSION 2.6)

set(GENERIC_FLAGS "-Wall -Wextra")

set(CMAKE_C_FLAGS_INIT   "-std=c11 ${GENERIC_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "-std=c++11 ${GENERIC_FLAGS}")
set(CMAKE_ASM_FLAGS_INIT "${GENERIC_FLAGS}")

unset(GENERIC_FLAGS)
