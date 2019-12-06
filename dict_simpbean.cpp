#include "dict_simpbean.h"

dict_simpBean::dict_simpBean()
{

}

QList<QMap<QString, QString> > dict_simpBean::getList() const
{
    return list;
}

void dict_simpBean::setList(const QList<QMap<QString, QString> > &value)
{
    list = value;
}

QString dict_simpBean::getVoc_pro() const
{
    return voc_pro;
}

void dict_simpBean::setVoc_pro(const QString &value)
{
    voc_pro = value;
}



