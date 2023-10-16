#include <QApplication>
#include "mainwindow.h"
#include "lib/MyTools.h"
#include "lib/FFmpegTool.h"
#include "lib/multithread.h"

int main(int argc, char *argv[]) {


    QApplication a (argc, argv);
    MainWindow w;
    w.show ();
    w.checkButtonStatus();


    return QApplication::exec ();
}
