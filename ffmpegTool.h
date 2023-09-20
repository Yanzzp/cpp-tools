#ifndef CPPJIEBA_FFMPEGTOOL_H
#define CPPJIEBA_FFMPEGTOOL_H
#include "mytools.h"

extern "C" {
#include <libavformat/avformat.h>
}
using namespace std;
class ffmpegTool {
private:
    static void customErrorCallback(void* avcl, int level, const char* fmt, va_list vl);
public:
    static int get_single_video_time(const string& filePath, bool isPrint= false);

    static void get_folder_videos_time(const string& folderPath, bool isPrint= false);

    void move_short_videos(const string& folderPath,int maxTime=120, bool isMove= false,bool isPrint= true);

};


#endif
