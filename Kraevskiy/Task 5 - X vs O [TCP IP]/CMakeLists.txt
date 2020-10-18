# cmake_minimum_required(VERSION <specify CMake version here>)
project(untitled2 C)

set(CMAKE_C_STANDARD 99)

link_libraries(ws2_32 wsock32)

add_executable(untitled2 main.c)
