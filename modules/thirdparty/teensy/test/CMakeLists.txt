cmake_minimum_required(VERSION 3.1)

set(NAME _test)
project(${NAME} CXX C ASM)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${NAME} main.cpp)
target_link_libraries(${NAME} ${CONAN_LIBS})
