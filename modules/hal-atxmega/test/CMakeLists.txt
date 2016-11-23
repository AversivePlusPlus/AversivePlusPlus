add_executable(atxmega_test test.cpp)
target_link_libraries(atxmega_test hal-atxmega Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
