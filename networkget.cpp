#include "networkget.h"

NetworkGet::NetworkGet(char*url,QWidget*widget)
{


    this->url=url;
    this->widget=widget;

    qDebug()<<"1";
    qDebug()<<QUrl(url);
    qDebug()<<"2";
}


void NetworkGet::run()
{
    QNetworkRequest request;

    manger = new QNetworkAccessManager;
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:70.0) Gecko/20100101 Firefox/70.0");

    request.setUrl(QUrl(url));

    qDebug()<<"1";
    qDebug()<<QUrl(url);
    qDebug()<<"2";
    manger->get(request);

    connect(manger,SIGNAL(finished(QNetworkReply*)), widget, SLOT(dictFind(QNetworkReply*)));
}
