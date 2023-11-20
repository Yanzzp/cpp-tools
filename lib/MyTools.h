
#ifndef CPP_TOOLS_H
#define CPP_TOOLS_H


#include <vector> // 包含向量库，用于存储文件名中的数字列表
#include <algorithm> // 包含算法库，用于对数字列表进行排序
#include <fstream>
#include <filesystem> // 包含文件系统库，用于处理文件和目录操作
#include <regex>
#include <thread>
#include <chrono>   // 包含时间库，用于计算函数运行时间
#include <mutex>
#include "tools.h"

#include "multithread.h"

#define print "print"
#define txt "txt"
#define copy "copy"


class FFmpegTool;


class MyTools : public Tools{
private:



    int imageCount = 0;
    int videoCount = 0;
    int audioCount = 0;

    std::vector<std::string> folder_info = {"", "", "", ""};

    uintmax_t folderSize = 0;
    std::mutex fileSizeMutex;



public:
    friend class FFmpegTool;



    uintmax_t get_file_size(std::string path);

    void print_all_files(const std::string &folderPath, int depth = 0);

//    void delete_files(const std::string &path, const std::string &name, bool isDelete = false, bool isPrint = true);

    void delete_files(const std::string &path, const std::vector<std::string> &names, bool isDelete = false, bool isPrint = true);

    void count_imgs_videos_and_audio(const std::string &folderPath, const std::string& option = "");

    void get_folder_size(const std::string &folderPath, bool isPrint = true, bool printAll = false, bool keepData = false);

    void multithread_get_folder_size(const std::string &folderPath, bool isPrint = true);

    void get_folder_info(const std::string &folderPath);

    void change_files_extension(const std::string &folderPath, std::string newExtension, std::string oldExtension = "",
                                bool isChange = false, bool option = false);

    void move_files_to_main_folder(const std::string &folderPath, bool isMove = false);

};


#endif
