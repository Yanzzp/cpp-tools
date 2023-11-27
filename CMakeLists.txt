cmake_minimum_required(VERSION 3.22.1)
project(cpp-tools)

set(CMAKE_CXX_STANDARD 23)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED libavcodec libavformat libavutil)
pkg_check_modules(HIREDIS REQUIRED hiredis)


# 包含 MySQL 头文件路径
include_directories(/usr/include/mysql)
include_directories(${HIREDIS_INCLUDE_DIRS})



#find_package(PythonLibs 3.10.12 REQUIRED)

# 假设腾讯云 SDK 安装在了 /path/to/tencentcloud-sdk 路径下
#set(TENCENTCLOUD_SDK_PATH "/home/yanzzp/Download/tencentcloud-sdk-cpp")

# 包含腾讯云 SDK 头文件
#include_directories(${TENCENTCLOUD_SDK_PATH}/include)

file(GLOB CURRENT_DIR_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)
file(GLOB_RECURSE LIB_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.h"
)
set(SOURCES ${CURRENT_DIR_SOURCES} ${LIB_SOURCES})

add_executable(cpp-tools ${SOURCES}
        lib/tools/python.cpp
        lib/tools/python.h
)


target_include_directories(cpp-tools PRIVATE
        ${FFMPEG_INCLUDE_DIRS}
        # 添加 MySQL 库文件路径
        /usr/lib/x86_64-linux-gnu
        #        ${PYTHON_INCLUDE_DIRS}
)

target_link_directories(cpp-tools PRIVATE
        ${FFMPEG_LIBRARY_DIRS}
        # 添加腾讯云 SDK 库文件目录
        #        ${TENCENTCLOUD_SDK_PATH}/lib
)

target_link_libraries(cpp-tools
        PRIVATE
        ${FFMPEG_LIBRARIES}
        mysqlclient
        mysqlcppconn
        ${HIREDIS_LIBRARIES}
#        ${PYTHON_LIBRARIES}
#        tencentcloud-sdk-cpp-core
)

