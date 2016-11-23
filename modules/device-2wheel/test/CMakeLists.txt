add_executable(device-2wheel_test test.cpp)
target_link_libraries(device-2wheel_test device-2wheel Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
