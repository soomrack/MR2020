cmake_minimum_required(VERSION 3.17)
project(Polish_notation)

set(CMAKE_CXX_STANDARD 14)

add_executable(Polish_notation main.cpp Polish_expression.cpp Polish_expression.h)