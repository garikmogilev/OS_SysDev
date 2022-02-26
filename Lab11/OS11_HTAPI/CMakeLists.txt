cmake_minimum_required(VERSION 3.21)
project(OS11_HTAPI)

set(CMAKE_CXX_STANDARD 17)

add_library(OS11_HTAPI SHARED main.cpp sources/CRUD.cpp sources/Element.cpp sources/HANDLE.cpp)

