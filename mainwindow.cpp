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
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_network = new SNetWork(this);
    connect(m_network, &SNetWork::sigReply,[=](QByteArray reply){
        ui->textEdit->setText(reply);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString urlstr = ui->lineEdit->text();
    if(urlstr != "") {
        qDebug() << "on_pushButton_clicked:" << urlstr;
        m_network->getRequest(QUrl(urlstr));
    }
}
