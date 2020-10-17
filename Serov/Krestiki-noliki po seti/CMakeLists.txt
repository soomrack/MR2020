# cmake_minimum_required(VERSION <specify CMake version here>)
project(untitled)

set(CMAKE_CXX_STANDARD 14)
link_libraries(ws2_32 wsock32)
add_executable(untitled main.cpp)