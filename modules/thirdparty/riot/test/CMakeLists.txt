cmake_minimum_required(VERSION 2.6)

set(NAME riot-test)
project(${NAME} CXX C ASM)

set(HAVE_FLAG_SEARCH_PATHS_FIRST 0)

file(GLOB_RECURSE INCLUDE_HPP "include/*.hpp")
file(GLOB_RECURSE INCLUDE_H "include/*.h")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

link_directories("${CONAN_LIB_DIRS}")
include_directories("${CONAN_INCLUDE_DIRS}")

set(SOURCE
  main.cpp
  )

add_executable(${NAME} ${SOURCE})

if(CONAN_LIBS)
  target_link_libraries(${NAME} ${CONAN_LIBS})
endif()
