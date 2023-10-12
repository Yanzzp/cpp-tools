#include <QApplication>
#include <QPushButton>
#include "lib/MyTools.h"
#include "lib/FFmpegTool.h"

int main(int argc, char *argv[]) {
    MyTools myTools;
    FFmpegTool ffmpegTool;

    myTools.print_all_files("E:\\MyCodeProject\\CLionProjects\\cpp-tools");
    ffmpegTool.get_single_video_time("E:\\分类\\千鹤酱的开发日记\\第二集.mp4",true);
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
