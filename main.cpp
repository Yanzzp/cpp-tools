#include "mytools.h"
#include "FFmpegToolBox.h"

using namespace std;
namespace fs = filesystem;

int main() {
    mytools tools;
    FFmpegToolBox ffmpegToolBox;
//    tools.create_txt_file("C:\\Users\\Administrator\\Desktop\\test\\test.txt");

//    ffmpegToolBox.get_all_videos_duration("E:\\分类\\资源\\Sin的礼品盒\\V", true);
    ffmpegToolBox.merge_videos("E:\\分类\\资源\\Sin的礼品盒\\V\\2018-2023-01.mp4","E:\\分类\\资源\\Sin的礼品盒\\V\\2018-2023-01.mp4");
    return 0;
}


