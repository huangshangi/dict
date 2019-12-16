#include "config.h"


Config::Config(QString fileName)
{
    if(fileName.isEmpty())
        this->fileName=QCoreApplication::applicationDirPath()+"/config.ini";
    else
        this->fileName=fileName;
    setting=new QSettings(this->fileName,QSettings::IniFormat);
}

void Config::set(QString section, QString name, QVariant value)
{
    setting->setValue(QString("%1/%2").arg(section).arg(name),value);

}

QVariant Config::get(QString section, QString name)
{
    return setting->value(QString("%1/%2").arg(section).arg(name));

}
