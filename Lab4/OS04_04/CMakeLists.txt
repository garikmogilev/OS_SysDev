cmake_minimum_required(VERSION 3.20)
project(OS04_04)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")
add_executable(OS04_04 main.cpp)
