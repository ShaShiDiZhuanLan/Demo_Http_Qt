#-------------------------------------------------
#
# Project created by QtCreator 2019-01-05T15:29:05 沙振宇
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo_Network
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    web/snetwork.cpp

HEADERS  += mainwindow.h \
    web/snetwork.h

FORMS    += mainwindow.ui
