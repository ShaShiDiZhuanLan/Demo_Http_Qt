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
#ifndef SNETWORK_H
#define SNETWORK_H

#include <QObject>
#include <QtNetwork/QtNetwork>
#include <QNetworkReply>
#include <QCryptographicHash>
#include <QDebug>
#include <QTimer>

class QReplyTimeout : public QObject
{
    Q_OBJECT
public:
    QReplyTimeout(QNetworkReply *reply, const int timeout) : QObject(reply) {
        if (reply && reply->isRunning()) {
            QTimer::singleShot(timeout, this, SLOT(onTimeout()));
        }
    }
signals:
    void sigTimeout();
private slots:
    void onTimeout() {
        QNetworkReply *reply = static_cast<QNetworkReply*>(parent());
        if (reply->isRunning()) {
            reply->abort();
            reply->deleteLater();
            emit sigTimeout();
        }
    }
};

class SNetWork : public QObject
{
    Q_OBJECT
public:
    explicit SNetWork(QObject * parent = 0);
    ~SNetWork();
    void getRequest(QUrl url); //get
    void postRequest(QUrl url, QByteArray data); //post
    void headRequest(QUrl url, QByteArray eid, QByteArray body = QByteArray()); //post setRawHeader
    QString getHostMacAddress(); // get mac address
signals:
    void sigReply(QByteArray reply);
    void sigReplyTimeout(QUrl url);
private slots:
    void replyFinish(QNetworkReply * reply);
private:
private:
    QNetworkAccessManager *m_manager = Q_NULLPTR;
    QNetworkRequest *m_postRequest = Q_NULLPTR;
    QNetworkRequest *m_getHeadRequest = Q_NULLPTR;
    QString m_mac;

};

#endif // SNETWORK_H

//-----------------------------
//json->data
//-----------------------------
//QJsonObject  json;
//json.insert("mac", m_mac);
//json.insert("soft_type", "3");
//json.insert("ext", msg);
//QJsonDocument document;
//document.setObject(json);
//QByteArray data = document.toJson(QJsonDocument::Compact);
