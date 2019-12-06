#ifndef DICT_WEBBEAN_H
#define DICT_WEBBEAN_H
#include <QMap>
#include <QString>
#include <QList>

class dict_webBean
{
public:
    dict_webBean();

private:
    QList<QMap<QString,QString>>list;
};

#endif // DICT_WEBBEAN_H
