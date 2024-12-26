cmake_minimum_required(VERSION 3.17)
project(factory_patterns)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(factory_patterns main.cpp)
