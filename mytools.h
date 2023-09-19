#ifndef CPPLEARNING_MYTOOLS_H
#define CPPLEARNING_MYTOOLS_H

#include <iostream> // 包含输入输出流库，用于输出信息到终端
#include <string> // 包含字符串库，用于处理文件名等字符串操作
#include <vector> // 包含向量库，用于存储文件名中的数字列表
#include <algorithm> // 包含算法库，用于对数字列表进行排序
#include <fstream>
#include <filesystem> // 包含文件系统库，用于处理文件和目录操作
#include <Windows.h>
#include <regex>

#include "cppjieba/Jieba.cpp"

#define txt "txt"
#define COPY "copy"


using namespace std;
namespace fs = filesystem;

using namespace std;

class mytools {
private:


    int imageCount = 0;
    int videoCount = 0;
    int audioCount = 0;

    const char* const DICT_PATH = "../dict/jieba.dict.utf8";
    const char* const HMM_PATH = "../dict/hmm_model.utf8";
    const char* const USER_DICT_PATH = "../dict/user.dict.utf8";
    const char* const IDF_PATH = "../dict/idf.utf8";
    const char* const STOP_WORD_PATH = "../dict/stop_words.utf8";

    std::vector<std::string> folder_info = {"", "", "", ""};
    uintmax_t folderSize = 0;

    static bool isImageFile(const std::string &filename);

    static bool isVideoFile(const std::string &filename);

    static bool isAudioFile(const std::string &filename);

    uintmax_t get_file_size(string path);

public:
    friend class FFmpegToolBox;

    void print_all_files(const string &folderPath, int depth = 0);

    void delete_files(const string &folderPath, string name, int depth = 0);

    void count_imgs_videos_and_audio(const string &folderPath, string option = "");

    void get_folder_size(const string &folderPath, bool isPrint = false);

    void get_folder_info(const string &folderPath);

    void change_files_extension(const string &folderPath, string newExtension, string oldExtension = "",
                                bool isChange = false, bool option = false);

    void find_name(const string &folderPath, string Name);

    void move_files_to_main_folder(const string &folderPath,bool isMove = false);

};


#endif
