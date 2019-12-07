#ifndef DICTBEAN_H
#define DICTBEAN_H
#include <QString>
#include <QList>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include "dict_simpbean.h"
#include "dict_webbean.h"
#include "dict_phrasebean.h"
#include "dict_examplebean.h"

class dictBean
{
public:

    dictBean();

    static dictBean fromJson(QString&json);


    QString getKeyword() const;
    void setKeyword(const QString &value);

    QString getTitle() const;
    void setTitle(const QString &value);

    QString getAudio() const;
    void setAudio(const QString &value);

    QList<dict_simpBean> getList() const;
    void setList(const QList<dict_simpBean> &value);

    QList<dict_webBean> getList_web() const;
    void setList_web(const QList<dict_webBean> &value);

    QList<dict_phraseBean> getList_phrase() const;
    void setList_phrase(const QList<dict_phraseBean> &value);

    QList<dict_exampleBean> getList_example() const;
    void setList_example(const QList<dict_exampleBean> &value);



private:
    QString keyword;
    QString title;
    QString audio;
    QList<dict_simpBean>list;
    QList<dict_webBean>list_web;
    QList<dict_phraseBean>list_phrase;
    QList<dict_exampleBean>list_example;
};

#endif // DICTBEAN_H
