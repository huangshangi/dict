#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>

class NetworkController
{

public:

    NetworkController();

    QTextCodec* codec;

    QNetworkAccessManager* manger;

    QNetworkRequest request;

    QNetworkReply* reply;

    QNetworkAccessManager* getUrl(char* url);
};

#endif // NETWORKCONTROLLER_H
