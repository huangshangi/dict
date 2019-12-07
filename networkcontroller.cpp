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


