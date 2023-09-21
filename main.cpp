#include "mytools.h"
#include "ffmpegTool.h"





int main() {

    mytools mytools;
    ffmpegTool ffmpeg;

    get_function_running_time([&](){
        mytools.get_folder_size("E:\\分类",true);
    });

    get_function_running_time([&](){
        mytools.multithread_get_folder_size("E:\\分类",true);
    });
    return 0;
}