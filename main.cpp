#include <iostream>
#include "mytools.h"

using namespace std;


int64_t GetFolderSize(const fs::path& folderPath) {
    int64_t size = 0;

    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
        if (fs::is_regular_file(entry)) {
            size += fs::file_size(entry);
        }
    }

    return size;
}

int main(){

    mytools tools;
//    tools.print_all_files("");
//    tools.delete_files("E:\\BaiduNetdiskDownload\\c++", "内存");
//    tools.countFiles("");
//    tools.printFiles("");
//    tools.count_imgs_and_videos("F:\\未分类\\BLUECAKE Hikari - Vol.04 BAD DOCTOR Succubus (+RED.Ver)  149P", "copy");
    cout << GetFolderSize("E:\\MyCodeProject\\CLionProjects\\CppTools\\CMakeLists.txt") << endl;
    return 0;
}

