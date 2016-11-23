add_executable(filter_test test.cpp)
target_link_libraries(filter_test filter Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
