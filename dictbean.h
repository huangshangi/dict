#ifndef DICTBEAN_H
#define DICTBEAN_H
#include <QString>
#include <QList>

class dictBean
{
public:

    dictBean();
    QString keyword;
    QString title;
    QString audio;
    QList<dict_simpBean>list;
    QList<dict_webBean>list_web;
    QList<dict_phraseBean>list_phrase;
    QList<dict_exampleBean>list_example;

    static dictBean fromJson(QString&json);
};

#endif // DICTBEAN_H
