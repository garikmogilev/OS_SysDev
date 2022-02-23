cmake_minimum_required(VERSION 3.21)
project(OS10_STATIC)

set(CMAKE_CXX_STANDARD 17)

add_library(OS10_STATIC HANDLE.cpp Element.cpp CRUD.cpp)
