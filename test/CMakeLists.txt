SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

ADD_EXECUTABLE(demo demo.cpp
        ../main.cpp)
ADD_EXECUTABLE(load_test load_test.cpp)
ADD_SUBDIRECTORY(unittest)
