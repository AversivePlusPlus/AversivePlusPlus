add_executable(memory_mapping_test test.cpp)
target_link_libraries(memory_mapping_test memory_mapping Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
