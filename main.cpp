#include <iostream>
#include "lib/FFmpegTool.h"

using namespace std;


int main() {
    FFmpegTool ffmpeg{.linuxMode=true};
    std::vector<std::string> properties = ffmpeg.check_video_properties(
            "E:\\分类\\BondageTea绳精病炮机调教合集【33V16GB】\\100.Sweet Girl Sexual Fantasies Part 2.mp4",
            false);
    for (const auto &property: properties) {
        std::cout << property << std::endl;
    }
//    ffmpeg.get_folder_video_properties("/home/yanzzp/MyCodeProject/CppProject/cpp-tools/v", false);

    return 0;
}
