#ifndef CONFIG_H
#define CONFIG_H
#include <QString>
#include <QVariant>
#include <QSettings>
#include <QtCore>
#include <QDebug>
class Config
{
public:

    Config(QString fileName="");
    void set(QString,QString,QVariant);
    QVariant get(QString,QString);

private:
    QSettings*setting;
    QString fileName;
};

#endif // CONFIG_H
