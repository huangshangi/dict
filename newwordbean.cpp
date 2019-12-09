#include "newwordbean.h"

newWordBean::newWordBean()
{

}

newWordBean::newWordBean(QString name, QString groupName, QString soundMark, QString explain)
{
    this->name=name;
    this->groupName=groupName;
    this->soundMark=soundMark;
    this->explain=explain;
}

newWordBean::newWordBean(QString name, QString groupName, QString soundMark, QString explain, QString dateAdd)
{
    this->name=name;
    this->groupName=groupName;
    this->soundMark=soundMark;
    this->explain=explain;
    this->dateAdd=dateAdd;
}

QString newWordBean::getName() const
{
    return name;
}

void newWordBean::setName(const QString &value)
{
    name = value;
}

QString newWordBean::getGroupName() const
{
    return groupName;
}

void newWordBean::setGroupName(const QString &value)
{
    groupName = value;
}

QString newWordBean::getSoundMark() const
{
    return soundMark;
}

void newWordBean::setSoundMark(const QString &value)
{
    soundMark = value;
}

QString newWordBean::getExplain() const
{
    return explain;
}

void newWordBean::setExplain(const QString &value)
{
    explain = value;
}

QString newWordBean::getDateAdd() const
{
    return dateAdd;
}

void newWordBean::setDateAdd(const QString &value)
{
    dateAdd = value;
}
