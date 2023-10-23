//
// Created by 11057 on 2023/10/16.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

int numb =0;
MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->pushButton_15, &QPushButton::pressed, this, &MainWindow::checkButtonStatus);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::checkButtonStatus() {
    bool isButtonPressed = ui->pushButton_15->isDown();

    if (isButtonPressed) {
        std::cout << "The button is pressed!"<<std::endl;
        qDebug() << "The button is pressed!";\
        numb++;
        ui->label->setText(QString::number(numb));
    } else {
        std::cout << "The button is not pressed!"<<std::endl;
        qDebug() << "The button is not pressed!";
    }
}
