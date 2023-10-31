#include "lib/HeadFile.h"

int main(int argc, char *argv[]) {
    MyTools myTools;

    myTools.delete_files("/mnt/e/迅雷下载",{"资源", "地址","务必","简评"}, true);
//    myTools.print_all_files("/mnt/e/迅雷下载", true);
    return 0;
}