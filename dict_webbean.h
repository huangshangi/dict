#ifndef DICT_WEBBEAN_H
#define DICT_WEBBEAN_H
#include <QMap>
#include <QString>
#include <QList>

class dict_webBean
{
public:
    dict_webBean();


    QMap<QString, QString> getMap() const;
    void setMap(const QMap<QString, QString> &value);

private:
    QMap<QString,QString>map;
};

#endif // DICT_WEBBEAN_H
