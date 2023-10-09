cmake_minimum_required(VERSION 3.26)
project(cpp-tools)

set(CMAKE_CXX_STANDARD 17)


find_package(OpenCV REQUIRED)
find_package(FFMPEG REQUIRED)


add_executable(cpp-tools main.cpp
        lib/MyTools.h
        lib/MyTools.cpp
        lib/FFmpegTool.h
        lib/FFmpegTool.cpp
        lib/multithread.h
        lib/CVTools.cpp
        lib/CVTools.h)



target_include_directories(cpp-tools PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(cpp-tools PRIVATE ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(cpp-tools ${OpenCV_LIBS}  ${FFMPEG_LIBRARIES})
