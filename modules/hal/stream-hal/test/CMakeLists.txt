add_executable(stream-hal_test test.cpp)
target_link_libraries(stream-hal_test stream-hal Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
