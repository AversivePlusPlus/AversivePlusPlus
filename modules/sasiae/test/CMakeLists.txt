find_package(Qt5Core)
find_package(Qt5Widgets) # this line should not be here, but it is compulsory under ubuntu

add_executable(sasiae_test test.cpp)
target_link_libraries(sasiae_test sasiae Qt5::Core Qt5::Widgets Aversive++ -Wl,-whole-archive startup -Wl,-no-whole-archive)
