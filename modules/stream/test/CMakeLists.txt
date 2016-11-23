add_executable(stream_test test.cpp)
target_link_libraries(stream_test stream Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
