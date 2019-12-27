#ifndef CONNECTPOOL_H
#define CONNECTPOOL_H
#include <QQueue>
#include <QString>
#include <QMutex>
#include <QMutexLocker>
#include <QWaitCondition>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QCoreApplication>
class ConnectPool
{
public:
    ConnectPool();

    ~ConnectPool();

    static QSqlDatabase openConnection();


    static void closeConnection(QSqlDatabase name);



private:

    int maxSize;//最大连接数
    int maxWaitTime;//获取一个连接所能容忍的最长等待时间
    int intervalTime;//获取一个连接的等待时间间隔
    QString databaseName;//要打开的数据库名称



    QQueue<QString>usedConnect;//已被使用的连接名
    QQueue<QString>unusedConnect;//未被使用的连接名

    static QMutex mutex;

    static ConnectPool*instance;

    static QWaitCondition waitCondition;

    static ConnectPool& getInstance();

    int getLength();//获取当前数据库连接数

    QSqlDatabase createConnection(QString& name);

};

#endif // CONNECTPOOL_H
