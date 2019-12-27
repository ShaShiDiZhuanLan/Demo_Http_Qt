/*-------------------------------------------------
#
# Project created by QtCreator
# Author: 沙振宇
# CreateTime: 2019-01-05
# UpdateTime: 2019-12-27
# Info: Qt调用HTTP请求的实例
# Url:https://shazhenyu.blog.csdn.net
# Github:https://github.com/ShaShiDiZhuanLan/Demo_Http_Qt
#
#-------------------------------------------------*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "web/snetwork.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    SNetWork* m_network = Q_NULLPTR;
};

#endif // MAINWINDOW_H
