cmake_minimum_required(VERSION 3.26)
project(cpp-tools)

set(CMAKE_CXX_STANDARD 20)


INCLUDE_DIRECTORIES(lib/jieba/deps/limonp/include
        lib/jieba/include)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set (CMAKE_INSTALL_PREFIX "/usr/local/cppjieba" CACHE PATH "default install path" FORCE )
endif()

ADD_DEFINITIONS(-O3 -Wall -g)



add_subdirectory(lib/jieba/deps)
add_subdirectory(lib/glfw)

if (WIN32)
    list(APPEND EXTRA_LIBS
        "-lglu32 -lopengl32"
    )
    set(CMAKE_EXE_LINKER_FLAGS "-std=c++11 -static-libgcc -static-libstdc++ -static")
endif ()
ENABLE_TESTING()
#ADD_TEST(NAME lib/jieba/test/test.run COMMAND lib/jieba/test/test.run)
#ADD_TEST(NAME ./load_test COMMAND ./load_test)
#ADD_TEST(NAME ./demo COMMAND ./demo)

include_directories(D:/zpplibrary/ffmpeg-win64-shared/include)
link_directories(D:/zpplibrary/ffmpeg-win64-shared/lib)

#include_directories(E:/MyCodeProject/CLionProjects/cpp-tools/SDL)


add_executable(cpp-tools main.cpp
        mytools.cpp
        mytools.h
        ffmpegTool.cpp
        ffmpegTool.h
        multithread.h
)


target_link_libraries(
        cpp-tools
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        postproc
        swresample
        swscale
        mingw32
        glfw
        ${EXTRA_LIBS}
)