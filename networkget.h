#ifndef NETWORKGET_H
#define NETWORKGET_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include <QMap>
#include <QWidget>
#include <QUrlQuery>
#include <QRunnable>
#include "mainwindow.h"
#include <QDebug>
class NetworkGet:public QRunnable,public QObject
{
public:
    NetworkGet(char* url,QWidget*widget);


    QNetworkAccessManager* manger;

    QNetworkRequest request;

    QNetworkReply* reply;

    char* url;

    QWidget*widget;

    QNetworkAccessManager* getUrl(char* url);

    void run();




};

#endif // NETWORKGET_H
