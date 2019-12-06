#ifndef DICT_PHRASEBEAN_H
#define DICT_PHRASEBEAN_H
#include <QMap>
#include <QString>
#include <QList>


class dict_phraseBean
{
public:
    dict_phraseBean();


    QMap<QString, QString> getMap() const;
    void setMap(const QMap<QString, QString> &value);

private:
    QMap<QString,QString>map;
};

#endif // DICT_PHRASEBEAN_H
