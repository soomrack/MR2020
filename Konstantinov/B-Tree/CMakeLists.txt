cmake_minimum_required(VERSION 3.19)
project(B_Tree)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-O0 -Wall -Wextra)


add_executable(B_Tree main.cpp b-tree.cpp b-tree.h)