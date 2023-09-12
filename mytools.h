
#ifndef CPPLEARNING_MYTOOLS_H
#define CPPLEARNING_MYTOOLS_H

#include <iostream> // 包含输入输出流库，用于输出信息到终端
#include <string> // 包含字符串库，用于处理文件名等字符串操作
#include <vector> // 包含向量库，用于存储文件名中的数字列表
#include <algorithm> // 包含算法库，用于对数字列表进行排序
#include <filesystem> // 包含文件系统库，用于处理文件和目录操作

using namespace std;
namespace fs = filesystem;

using namespace std;

class mytools {
public:
    void print_all_files(const string &path, int depth = 0);

    void delete_files(const string &path, string name, int depth = 0);

    void test();
};


#endif //CPPLEARNING_MYTOOLS_H
