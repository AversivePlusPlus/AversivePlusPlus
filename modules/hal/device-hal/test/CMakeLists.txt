add_executable(device-hal_test test.cpp)
target_link_libraries(device-hal_test device-hal Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
