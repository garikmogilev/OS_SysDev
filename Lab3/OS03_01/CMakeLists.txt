cmake_minimum_required(VERSION 3.20)
project(OS03_01)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")
add_executable(OS03_01 main.cpp)
