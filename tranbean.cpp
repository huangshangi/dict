#include "tranbean.h"

tranBean::tranBean()
{

}

tranBean tranBean::fromJson(QString &json)
{
    QByteArray data=json.toUtf8();
    qDebug()<<json;
    QJsonParseError parseError;
    tranBean bean;

    QJsonDocument document=QJsonDocument::fromJson(data,&parseError);

    if(parseError.error==QJsonParseError::NoError&&document.isObject()){
        QJsonObject obj=document.object();
        qDebug()<<"22";
        if(obj.contains("src"))
            bean.setSrc(obj.value("src").toString());

        if(obj.contains("content"))
            bean.setContent(obj.value("content").toString());

        if(obj.contains("audio"))
            bean.setAudio(obj.value("audio").toString());

        return bean;

    }

    return bean;

}

QString tranBean::getSrc() const
{
    return src;
}

void tranBean::setSrc(const QString &value)
{
    src = value;
}

QString tranBean::getContent() const
{
    return content;
}

void tranBean::setContent(const QString &value)
{
    content = value;
}

QString tranBean::getAudio() const
{
    return audio;
}

void tranBean::setAudio(const QString &value)
{
    audio = value;
}
