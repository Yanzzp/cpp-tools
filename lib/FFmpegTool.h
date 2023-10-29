#pragma once
#ifndef CPP_TOOLS_FFMPEGTOOL_H
#define CPP_TOOLS_FFMPEGTOOL_H

#include "MyTools.h"
#include "multithread.h"
extern "C" {
#include <libavformat/avformat.h>
}


class MyTools;

class FFmpegTool {
private:
    static void customErrorCallback(void* avcl, int level, const char* fmt, va_list vl);
public:
    static int get_single_video_time(const std::string& filePath, bool isPrint= false);

    static void get_folder_videos_time(const std::string& folderPath, bool isPrint= false);

    void move_short_videos(const std::string& folderPath,int maxTime=120, bool isMove= false,bool isPrint= true);

};

#endif
