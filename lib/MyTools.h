#pragma once
#ifndef CPP_TOOLS_H
#define CPP_TOOLS_H

#include <iostream> // 包含输入输出流库，用于输出信息到终端
#include <string> // 包含字符串库，用于处理文件名等字符串操作
#include <vector> // 包含向量库，用于存储文件名中的数字列表
#include <algorithm> // 包含算法库，用于对数字列表进行排序
#include <fstream>
#include <filesystem> // 包含文件系统库，用于处理文件和目录操作
#include <regex>
#include <thread>
#include <chrono>   // 包含时间库，用于计算函数运行时间
#include <mutex>
#include <set>


#include "multithread.h"

#define txt "txt"
#define COPY "copy"


class FFmpegTool;


class MyTools {
private:

    int imageCount = 0;
    int videoCount = 0;
    int audioCount = 0;

    std::vector<std::string> folder_info = {"", "", "", ""};

    uintmax_t folderSize = 0;
    std::mutex fileSizeMutex;

    static const std::set<std::string> imageExtensions;
    static const std::set<std::string> videoExtensions;
    static const std::set<std::string> audioExtensions;

    static bool isImageFile(const std::string &filename);

    static bool isVideoFile(const std::string &filename);

    static bool isAudioFile(const std::string &filename);

    uintmax_t get_file_size(std::string path);


public:
    friend class FFmpegTool;

    void print_all_files(const std::string &folderPath, int depth = 0);

    void delete_files(const std::string &path, const std::string &name, bool isDelete = false, bool isPrint = true);

    void count_imgs_videos_and_audio(const std::string &folderPath, std::string option = "");

    void get_folder_size(const std::string &folderPath, bool isPrint = true, bool printAll = false, bool keepData = false);

    void multithread_get_folder_size(const std::string &folderPath, bool isPrint = true);

    void get_folder_info(const std::string &folderPath);

    void change_files_extension(const std::string &folderPath, std::string newExtension, std::string oldExtension = "",
                                bool isChange = false, bool option = false);

    void move_files_to_main_folder(const std::string &folderPath, bool isMove = false);

};


#endif
