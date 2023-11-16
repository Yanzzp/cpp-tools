cmake_minimum_required(VERSION 3.22.1)
project(cpp-tools)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED libavcodec libavformat libavutil)

#find_package(PythonLibs 3.10.12 REQUIRED)

# 假设腾讯云 SDK 安装在了 /path/to/tencentcloud-sdk 路径下
#set(TENCENTCLOUD_SDK_PATH "/home/yanzzp/Download/tencentcloud-sdk-cpp")

# 包含腾讯云 SDK 头文件
include_directories(${TENCENTCLOUD_SDK_PATH}/include)

add_executable(cpp-tools main.cpp
        lib/MyTools.cpp
        lib/FFmpegTool.cpp
        lib/plugs.h
        lib/threadpools.h
)

target_include_directories(cpp-tools PRIVATE
        ${FFMPEG_INCLUDE_DIRS}
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
#        ${PYTHON_LIBRARIES}
        # 链接腾讯云 SDK 核心库
#        tencentcloud-sdk-cpp-core
)

