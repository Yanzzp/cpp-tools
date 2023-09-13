cmake_minimum_required(VERSION 3.26)
project(CppTools)

set(CMAKE_CXX_STANDARD 17)

include_directories(C:\\Users\\11057\\miniconda3\\include)


link_libraries(C:/Users/11057/miniconda3/libs/python311.lib)


add_executable(CppTools main.cpp
        mytools.cpp
        mytools.h)
