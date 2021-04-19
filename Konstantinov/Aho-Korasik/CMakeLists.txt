cmake_minimum_required(VERSION 3.19)
project(Aho_Korasik)

set(CMAKE_CXX_STANDARD 14)

add_compile_options(-O0 -Wall -Werror)


add_executable(Aho_Korasik main.cpp Aho_Corasick.cpp Aho_Corasick.h)