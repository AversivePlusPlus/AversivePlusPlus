add_executable(stm32cubef4_test test.cpp)
target_link_libraries(stm32cubef4_test hal-stm32cubef4 Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
