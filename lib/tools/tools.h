#ifndef CPP_TOOLS_TOOLS_H
#define CPP_TOOLS_TOOLS_H

#include <iostream>
#include <fstream>
#include <filesystem> // 包含文件系统库，用于处理文件和目录操作
#include <set>
#include <vector> // 包含向量库，用于存储文件名中的数字列表
#include <algorithm> // 包含算法库，用于对数字列表进行排序
#include <regex>
#include <thread>
#include <chrono>   // 包含时间库，用于计算函数运行时间
#include <mutex>

#include "../pools/threadpools.h"
#include "../multithread.h"


class Tools {
private:
protected:
    static const std::set<std::string> imageExtensions;
    static const std::set<std::string> videoExtensions;
    static const std::set<std::string> audioExtensions;
public:
    static bool linuxMode;

    static bool isImageFile(const std::string &filename);

    static bool isVideoFile(const std::string &filename);

    static bool isAudioFile(const std::string &filename);

    static std::string windows_path_to_linux_path(std::string path);

    static std::string linux_path_to_windows_path(std::string path);

    static std::string copy_to_clipboard(std::string str);

    std::string exec_command(const char* cmd);
};


#endif //CPP_TOOLS_TOOLS_H
