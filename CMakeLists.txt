cmake_minimum_required(VERSION 3.20)

project(threadpool VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(threadpool src/example.cpp)
