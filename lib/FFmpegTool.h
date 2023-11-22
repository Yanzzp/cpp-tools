#pragma once
#ifndef CPP_TOOLS_FFMPEGTOOL_H
#define CPP_TOOLS_FFMPEGTOOL_H

#include "tools.h"

extern "C" {
#include <libavformat/avformat.h>
}


class FileOrganizer;

class FFmpegTool : public Tools {
private:

    static void customErrorCallback(void *avcl, int level, const char *fmt, va_list vl);

public:
    friend class FileOrganizer;

    static std::string convert_seconds_to_time_format(int total_seconds);

    static int get_single_video_time(const std::string &filePath, bool isPrint = false);

    static std::vector<std::string> get_video_details(const std::string &filePath);

    static void get_folder_videos_time(const std::string &folderPath, bool isPrint = false);

    static void
    move_short_videos(const std::string &folderPath, int maxTime = 120, bool isMove = false, bool isPrint = true);

    static std::vector<std::string> check_video_properties(const std::string &filePath, bool isPrint = false);

    static void get_folder_video_properties(const std::string &filePath, bool isPrint = false);
};

#endif
