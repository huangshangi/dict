#ifndef DICT_PHRASEBEAN_H
#define DICT_PHRASEBEAN_H
#include <QMap>
#include <QString>
#include <QList>


class dict_phraseBean
{
public:
    dict_phraseBean();
private:
    QList<QMap<QString,QString>>list;
};

#endif // DICT_PHRASEBEAN_H
