#ifndef DICT_SIMPBEAN_H
#define DICT_SIMPBEAN_H

#include <QString>
#include <QMap>
#include <QList>

class dict_simpBean
{
public:
    dict_simpBean();




    QList<QMap<QString, QString> > getList() const;
    void setList(const QList<QMap<QString, QString> > &value);

    QString getVoc_pro() const;
    void setVoc_pro(const QString &value);

private:
    QString voc_pro;//单词读音
    QList<QMap<QString,QString>> list;
};

#endif // DICT_SIMPBEAN_H
