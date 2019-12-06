#include "dict_examplebean.h"

dict_exampleBean::dict_exampleBean()
{

}

QMap<QString, QString> dict_exampleBean::getMap() const
{
    return map;
}

void dict_exampleBean::setMap(const QMap<QString, QString> &value)
{
    map = value;
}


