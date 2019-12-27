#ifndef TRANBEAN_H
#define TRANBEAN_H
#include <QString>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
class tranBean
{
public:
    tranBean();

    static tranBean fromJson(QString &json);

    QString getSrc() const;
    void setSrc(const QString &value);

    QString getContent() const;
    void setContent(const QString &value);

    QString getAudio() const;
    void setAudio(const QString &value);

private:
    QString src;
    QString content;
    QString audio;
};

#endif // TRANBEAN_H
