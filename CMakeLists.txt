cmake_minimum_required(VERSION 3.26)
project(cpp-tools)

set(CMAKE_CXX_STANDARD 17)


find_package(OpenCV CONFIG REQUIRED)
find_package(FFMPEG REQUIRED)

add_executable(cpp-tools main.cpp
        lib/MyTools.h
        lib/MyTools.cpp
        lib/FFmpegTool.h
        lib/FFmpegTool.cpp
        lib/multithread.h)

target_link_libraries(cpp-tools PRIVATE ${OpenCV_LIBS})
target_include_directories(cpp-tools PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(cpp-tools PRIVATE ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(cpp-tools PRIVATE ${FFMPEG_LIBRARIES})