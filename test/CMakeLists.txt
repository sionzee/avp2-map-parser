cmake_minimum_required(VERSION 3.16)
project(Test)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-DMAPS_PATH=\"${CMAKE_SOURCE_DIR}/test/maps\")

add_executable(Test main.cpp lib/catch.hpp worlds_test.cpp)
target_link_libraries(Test PRIVATE AVP2MapReaderLib)
