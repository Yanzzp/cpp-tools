cmake_minimum_required(VERSION 3.22.1)
project(cpp-tools)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 添加一个选项，默认为ON
option(USE_QT "Use Qt for the project" OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED libavcodec libavformat libavutil)

# 只有当USE_QT被设为ON时，才会寻找Qt库
if(USE_QT)
    find_package(Qt5 COMPONENTS
            Core
            Gui
            Widgets
            REQUIRED)
endif()

add_executable(cpp-tools main.cpp
        lib/MyTools.cpp
        lib/FFmpegTool.cpp
        lib/HeadFile.h
)

target_include_directories(cpp-tools PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(cpp-tools PRIVATE ${FFMPEG_LIBRARY_DIRS})

# 根据是否使用Qt来链接库
if(USE_QT)
    target_link_libraries(cpp-tools
            PRIVATE
            ${FFMPEG_LIBRARIES}
            Qt::Core
            Qt::Gui
            Qt::Widgets
    )
else()
    target_link_libraries(cpp-tools
            PRIVATE
            ${FFMPEG_LIBRARIES}
    )
endif()
