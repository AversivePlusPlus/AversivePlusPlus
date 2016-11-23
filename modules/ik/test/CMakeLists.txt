add_executable(ik_test test.cpp)
target_link_libraries(ik_test ik Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
