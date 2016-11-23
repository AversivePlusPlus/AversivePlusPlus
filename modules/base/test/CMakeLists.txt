add_executable(base_test test.cpp)
target_link_libraries(base_test base Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
