project(xoo C)

set(CMAKE_C_STANDARD 99)

link_libraries(ws2_32 wsock32)

add_executable(xoo main.c)