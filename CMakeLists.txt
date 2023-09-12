cmake_minimum_required(VERSION 3.26)
project(CppTools)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppTools main.cpp
        mytools.cpp
        mytools.h)
