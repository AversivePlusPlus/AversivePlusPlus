add_executable(device-control_test test.cpp)
target_link_libraries(device-control_test device-control Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
