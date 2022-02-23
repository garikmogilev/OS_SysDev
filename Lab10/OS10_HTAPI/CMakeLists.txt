cmake_minimum_required(VERSION 3.21)
project(OS10_HTAPI)

set(CMAKE_CXX_STANDARD 17)

add_executable(OS10_HTAPI main.cpp)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -static")
target_link_libraries(OS10_HTAPI ${CMAKE_SOURCE_DIR}/../OS10_STATIC/cmake-build-debug/libOS10_STATIC.a)
