cmake_minimum_required(VERSION 3.17)
project(factory_patterns)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(simple_factory simple_factory.cpp)
add_executable(factory factory.cpp)
add_executable(abstract_factory abstract_factory.cpp)