cmake_minimum_required(VERSION 3.16)
project(AVP2MapReader)

set(CMAKE_CXX_STANDARD 20)

add_executable(AVP2MapReader main.cpp)
add_library(AVP2MapReaderLib types/Vector.h utils/BinaryStream.h utils/BinaryStream.cpp types/WorldTree.h api/Map.h api/WorldFlags.h core/Processor.cpp core/Processor.h)

target_link_libraries(AVP2MapReader PRIVATE AVP2MapReaderLib)
