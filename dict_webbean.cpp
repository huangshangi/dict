#include "dict_webbean.h"

dict_webBean::dict_webBean()
{

}

QMap<QString, QString> dict_webBean::getMap() const
{
    return map;
}

void dict_webBean::setMap(const QMap<QString, QString> &value)
{
    map = value;
}

