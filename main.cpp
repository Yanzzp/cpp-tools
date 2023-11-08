#include <iostream>
#include "lib/FFmpegTool.h"
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

using namespace std;




int main() {
    // 这里直接设置视频文件的路径
//    string videoPath1 = "../test1.mkv";
//    string videoPath2 = "../test2.mkv";
    FFmpegTool ffmpegTool;

    // 注册所有的编解码器和格式等

    // 检查第一个视频文件的属性
    vector<string> result1 = ffmpegTool.check_video_properties("../test1.mkv",true);
    // 检查第二个视频文件的属性
    vector<string> result2 = ffmpegTool.check_video_properties("../test2.mkv",true);

    // 如果任一文件检查失败，则退出
    for(auto i:result1){
        cout<<i<<endl;
    }


    return 0;
}
