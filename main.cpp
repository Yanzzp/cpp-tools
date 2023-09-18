#include "cppjieba/Jieba.cpp"
#include <iostream>
#include <filesystem>
#include "mytools.h"

using namespace std;
namespace fs = filesystem;

int main() {
    mytools tools;

//    tools.create_txt_file("C:\\Users\\Administrator\\Desktop\\test\\test.txt");
    tools.move_files_to_main_folder("E:\\BaiduNetdiskDownload\\小祈愿");


    return 0;
}
