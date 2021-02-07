cmake_minimum_required(VERSION 3.17)
project(Sort)

set(CMAKE_CXX_STANDARD 11)

add_library(Sort SHARED main.cpp Sort.cpp Sort.h)