#ifndef CPPJIEBA_FFMPEGTOOLBOX_H
#define CPPJIEBA_FFMPEGTOOLBOX_H

#include "mytools.h"
#include <chrono>
#include <ctime>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}

class FFmpegToolBox {
private:


    static void customErrorCallback(void *avcl, int level, const char *fmt, va_list vl);

public:
    class mytools tools;

    static vector<string> get_video_duration(const std::string &filePath, bool isPrint = false);

    static void get_all_videos_duration(const std::string &filePath, bool isPrint = false);

    int merge_videos(string folderPath1,string folderPath2);
};


#endif
