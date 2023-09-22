#include "mytools.h"
#include "ffmpegTool.h"


extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/avutil.h>
#include <libavcodec/avcodec.h>
}



int main() {

    mytools mytools;
    ffmpegTool ffmpeg;

//    get_function_running_time([&](){
//        mytools.multithread_get_folder_size("E:\\分类",true);
//    });
    cout << avcodec_configuration() << endl;
    return 0;
}