#ifndef DICT_EXAMPLEBEAN_H
#define DICT_EXAMPLEBEAN_H
#include <QMap>
#include <QString>
#include <QList>


class dict_exampleBean
{
public:
    dict_exampleBean();
private:
    QList<QMap<QString,QString>>list;
};

#endif // DICT_EXAMPLEBEAN_H
