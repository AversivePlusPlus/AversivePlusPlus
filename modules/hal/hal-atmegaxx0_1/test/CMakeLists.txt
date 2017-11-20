add_executable(atmega2560_test test.cpp)
target_link_libraries(atmega2560_test hal-atmegaxx0_1 Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
