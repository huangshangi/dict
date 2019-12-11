#include "networkcontroller.h"

NetworkController::NetworkController()
{
    manger = new QNetworkAccessManager;
    codec = QTextCodec::codecForName("GB2312");
}

QNetworkAccessManager* NetworkController::getUrl(char* u)
{
    QNetworkRequest request;
    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:70.0) Gecko/20100101 Firefox/70.0");

    request.setUrl(QUrl(codec->toUnicode(u)));

    manger->get(request);

    return manger;
}

QNetworkAccessManager *NetworkController::postUrl(char *url, QMap<QString, QString>map)
{
    QNetworkRequest request;
    QUrlQuery urlQuery;
    QMap<QString,QString>::const_iterator it;
    for(it=map.cbegin();it!=map.cend();it++)
        urlQuery.addQueryItem(it.key(),it.value());

    request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:70.0) Gecko/20100101 Firefox/70.0");

    request.setUrl(QUrl(codec->toUnicode(url)));

    manger->post(request,urlQuery.toString().toUtf8());

    return manger;
}


