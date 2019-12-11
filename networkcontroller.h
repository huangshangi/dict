#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include <QMap>
#include <QUrlQuery>
class NetworkController
{

public:

    NetworkController();

    QTextCodec* codec;

    QNetworkAccessManager* manger;

    QNetworkRequest request;

    QNetworkReply* reply;

    QNetworkAccessManager* getUrl(char* url);

    QNetworkAccessManager*postUrl(char*url,QMap<QString,QString>);


};

#endif // NETWORKCONTROLLER_H
