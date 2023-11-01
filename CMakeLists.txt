cmake_minimum_required(VERSION 3.22.1)
project(cpp-tools)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED libavcodec libavformat libavutil)

#find_package(Qt5 COMPONENTS
#        Core
#        Gui
#        Widgets
#        REQUIRED)

find_package(PythonLibs 3.10.12 REQUIRED)

add_executable(cpp-tools main.cpp
        lib/MyTools.cpp
        lib/FFmpegTool.cpp
        lib/plugs.h
)

target_include_directories(cpp-tools PRIVATE ${FFMPEG_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})

target_link_directories(cpp-tools PRIVATE ${FFMPEG_LIBRARY_DIRS})

target_link_libraries(cpp-tools
        PRIVATE
        ${FFMPEG_LIBRARIES}
#        Qt::Core
#        Qt::Gui
#        Qt::Widgets
        ${PYTHON_LIBRARIES}
)
