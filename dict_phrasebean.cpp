#include "dict_phrasebean.h"

dict_phraseBean::dict_phraseBean()
{

}

QMap<QString, QString> dict_phraseBean::getMap() const
{
    return map;
}

void dict_phraseBean::setMap(const QMap<QString, QString> &value)
{
    map = value;
}

