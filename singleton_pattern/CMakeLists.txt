cmake_minimum_required(VERSION 3.17)
project(singleton_pattern)

set(CMAKE_CXX_STANDARD 11)

add_executable(singleton_pattern main.cpp)

target_link_libraries(singleton_pattern pthread)