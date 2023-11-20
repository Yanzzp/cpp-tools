#pragma once
#ifndef CPP_TOOLS_FFMPEGTOOL_H
#define CPP_TOOLS_FFMPEGTOOL_H

#include "tools.h"
extern "C" {
#include <libavformat/avformat.h>
}


class FileOrganizer;

class FFmpegTool : public Tools{
private:

    static void customErrorCallback(void* avcl, int level, const char* fmt, va_list vl);

    static std::string windows_path_to_linux_path(std::string path);
public:
    static int get_single_video_time(const std::string& filePath, bool isPrint= false);

    void get_folder_videos_time(const std::string& folderPath, bool isPrint= false);

    void move_short_videos(const std::string& folderPath,int maxTime=120, bool isMove= false,bool isPrint= true);

    std::vector<std::string> check_video_properties(const std::string &filePath, bool isPrint = false);

    void get_folder_video_properties(const std::string &filePath, bool isPrint = false);
};

#endif
