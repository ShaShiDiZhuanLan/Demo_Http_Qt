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
#include "snetwork.h"
#include <QDateTime>
#define POST_TIMEOUT 4000

SNetWork::SNetWork(QObject *parent): QObject(parent)
{
    m_manager = new QNetworkAccessManager(this);
    m_postRequest = new QNetworkRequest();
    m_getHeadRequest = new QNetworkRequest();
    m_postRequest->setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    connect(m_manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinish(QNetworkReply*)));
}

SNetWork::~SNetWork()
{
    if(m_postRequest) {
        delete m_postRequest;
        m_postRequest = Q_NULLPTR;
    }
    if(m_getHeadRequest) {
        delete m_getHeadRequest;
        m_getHeadRequest = Q_NULLPTR;
    }
}

void SNetWork::getRequest(QUrl url)
{
    m_manager->get(QNetworkRequest(url));
}

void SNetWork::postRequest(QUrl url, QByteArray data)
{
    qDebug() << "post:" << url << data;
    m_postRequest->setUrl(url);
    QNetworkReply* pReply = m_manager->post(*m_postRequest, data);

    QReplyTimeout *pTimeout = new QReplyTimeout(pReply, POST_TIMEOUT);
    // time out
    connect(pTimeout, &QReplyTimeout::sigTimeout, [=]() {
        emit sigReplyTimeout(url);
    });
}

void SNetWork::headRequest(QUrl url, QByteArray eid, QByteArray body)
{
    m_getHeadRequest->setUrl(url);
    m_getHeadRequest->setRawHeader("eId", eid);// set eid
    m_manager->post(*m_getHeadRequest, body);
}

void SNetWork::replyFinish(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        // To do error deal
        qDebug() << "SNetWork Error String: " << reply->error() << "error str:" << reply->errorString();
        return;
    }
    QByteArray byteArray = reply->readAll();

    qDebug() << "replyFinish:" << byteArray;
    emit sigReply(byteArray);
}

QString SNetWork::getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    int nCnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++) {
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack)) {
            strMacAddr = nets[i].hardwareAddress();
            break;
        }
    }
    QString tmp;
    if(strMacAddr.contains(":")) {
        QStringList ltmp = strMacAddr.split(":");
        for(int i = 0; i < ltmp.count(); i++) {
            tmp.append(ltmp.at(i));
            if(i != (ltmp.count() - 1)) {
                tmp.append("-");
            }
        }
    }
    return tmp;
}
