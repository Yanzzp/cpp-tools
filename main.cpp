#include "cppjieba/Jieba.cpp"
#include <iostream>
#include "mytools.h"

using namespace std;


int main() {
    mytools tools;

//    tools.create_txt_file("C:\\Users\\Administrator\\Desktop\\test\\test.txt");
    tools.find_pornographic("G:\\资源", "G:\\资源\\test.txt");


    return 0;
}
