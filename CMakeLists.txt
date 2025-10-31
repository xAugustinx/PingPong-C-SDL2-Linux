cmake_minimum_required(VERSION 4.1)
project(pingPong C)

set(CMAKE_C_STANDARD 11)

add_executable(pingPong main.c)


find_package(SDL2 REQUIRED)
target_link_libraries(pingPong PRIVATE SDL2::SDL2)