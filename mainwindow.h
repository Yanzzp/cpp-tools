//
// Created by 11057 on 2023/10/16.
//

#ifndef CPP_TOOLS_MAINWINDOW_H
#define CPP_TOOLS_MAINWINDOW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
};


#endif //CPP_TOOLS_MAINWINDOW_H
