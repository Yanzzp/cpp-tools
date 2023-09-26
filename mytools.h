#ifndef CPP_TOOLS_H
#define CPP_TOOLS_H

#include <iostream> // 包含输入输出流库，用于输出信息到终端
#include <string> // 包含字符串库，用于处理文件名等字符串操作
#include <vector> // 包含向量库，用于存储文件名中的数字列表
#include <algorithm> // 包含算法库，用于对数字列表进行排序
#include <fstream>
#include <filesystem> // 包含文件系统库，用于处理文件和目录操作
#include <Windows.h>
#include <regex>
#include "thread"
#include <chrono>
#include <mutex>

#include "ffmpegTool.h"
#include "cppjieba/Jieba.cpp"

#define txt "txt"
#define COPY "copy"

#define get_function_run_time(code_block) \
    { \
        get_function_running_time([&]() { \
            code_block \
        }); \
    }


template<typename Func>
void get_function_running_time(Func func) {

    auto startTime = std::chrono::high_resolution_clock::now();
    func();
    auto endTime = std::chrono::high_resolution_clock::now();
    // 计算时间间隔
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
//    std::cout << "函数" << "的执行时间: " << duration.count() << "ms" << std::endl;
}


class mytools {
private:

    int imageCount = 0;
    int videoCount = 0;
    int audioCount = 0;

    const char *const DICT_PATH = "../dict/jieba.dict.utf8";
    const char *const HMM_PATH = "../dict/hmm_model.utf8";
    const char *const USER_DICT_PATH = "../dict/user.dict.utf8";
    const char *const IDF_PATH = "../dict/idf.utf8";
    const char *const STOP_WORD_PATH = "../dict/stop_words.utf8";

    std::vector<std::string> folder_info = {"", "", "", ""};
    uintmax_t folderSize = 0;
    std::mutex folderSizeMutex;

    static bool isImageFile(const std::string &filename);

    static bool isVideoFile(const std::string &filename);

    static bool isAudioFile(const std::string &filename);

    uintmax_t get_file_size(std::string path);


public:
    friend class ffmpegTool;

    void print_all_files(const std::string &folderPath, int depth = 0);

    void delete_files(const std::string &folderPath, std::string name, int depth = 0);

    void count_imgs_videos_and_audio(const std::string &folderPath, std::string option = "");

    void
    get_folder_size(const std::string &folderPath, bool isPrint = true, bool printAll = false, bool keepData = false);

    void get_folder_info(const std::string &folderPath);

    void change_files_extension(const std::string &folderPath, std::string newExtension, std::string oldExtension = "",
                                bool isChange = false, bool option = false);

    void find_name(const std::string &folderPath, std::string Name);

    void move_files_to_main_folder(const std::string &folderPath, bool isMove = false);

    void multithread_get_folder_size(const std::string &folderPath, bool isPrint = true);

};


#endif
