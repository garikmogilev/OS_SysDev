cmake_minimum_required(VERSION 3.21)
project(OS10_01)

set(CMAKE_CXX_STANDARD 23)
# executable
add_executable(OS10_01 main.cpp headers/HANDLE.h sources/HANDLE.cpp headers/CRUD.h headers/Element.h sources/Element.cpp sources/CRUD.cpp )
# add static lib
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")