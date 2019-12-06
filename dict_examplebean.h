#ifndef DICT_EXAMPLEBEAN_H
#define DICT_EXAMPLEBEAN_H
#include <QMap>
#include <QString>
#include <QList>


class dict_exampleBean
{
public:
    dict_exampleBean();


    QMap<QString, QString> getMap() const;
    void setMap(const QMap<QString, QString> &value);

private:
    QMap<QString,QString>map;
};

#endif // DICT_EXAMPLEBEAN_H
