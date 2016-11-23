add_executable(cas_test test.cpp)
target_link_libraries(cas_test cas Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
