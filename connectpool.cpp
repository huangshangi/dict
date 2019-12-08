#include "connectpool.h"
#define MAXCOUNT 50
#define TIMEINTERVAL 200
#define MAXWAITTIME 1000
#define DATABASENAME "C:\\Users\\hzh17\\Desktop\\dict.db";



QMutex ConnectPool::mutex;
QWaitCondition ConnectPool::waitCondition;
ConnectPool* ConnectPool::instance = NULL;
ConnectPool::ConnectPool()
{
    maxSize=MAXCOUNT;
    intervalTime=TIMEINTERVAL;
    maxWaitTime=MAXWAITTIME;
    databaseName=DATABASENAME;

}

//清除所有连接
ConnectPool::~ConnectPool()
{



}

QSqlDatabase ConnectPool::openConnection()
{

    ConnectPool instance=ConnectPool::getInstance();
    QMutexLocker locker(&mutex);

    QSqlDatabase sqlLink;
    QString name;
    //当前已创建连接数
    int count=instance.getLength();


    for(int i=0;(i<instance.maxSize)&&(instance.unusedConnect.size()==0)&&(count==instance.maxSize);i+=instance.intervalTime){
        waitCondition.wait(&mutex,instance.intervalTime);
        count=instance.getLength();
    }

    /*1.查看当前是否有可复用的连接
     *2.若当前没有可复用的连接 且当前连接数小于最大连接数 创建一个新连接
     */
    if(instance.unusedConnect.size()>0)
        name=instance.unusedConnect.dequeue();
    else if(count<instance.maxSize)
        name=QString("sqlConnect-%1").arg(count);


    sqlLink=instance.createConnection(name);
    if(sqlLink.isOpen())
        instance.usedConnect.enqueue(name);


    return sqlLink;

}

void ConnectPool::closeConnection(QSqlDatabase link)
{
    ConnectPool& dbPool=ConnectPool::getInstance();

    QString name=link.connectionName();

    if(dbPool.usedConnect.contains(name)){
        QMutexLocker locker(&mutex);
        dbPool.usedConnect.removeOne(name);
        dbPool.unusedConnect.enqueue(name);
        waitCondition.wakeOne();
    }
}

int ConnectPool::getLength()
{
    return instance->usedConnect.size()+instance->unusedConnect.size();
}

QSqlDatabase ConnectPool::createConnection(QString& name)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains(name)){
        db=QSqlDatabase::database(name);
        if(!db.isOpen())
            return QSqlDatabase();
        return db;
    }else{
        db=QSqlDatabase::addDatabase("QSQLITE",name);
        db.setDatabaseName(databaseName);
        if(!db.open())
            return QSqlDatabase();
        return db;
    }
}

ConnectPool& ConnectPool::getInstance()
{

    if(instance==NULL){

        QMutexLocker locker(&mutex);
        if(instance==NULL){
            instance=new ConnectPool();
        }
    }

    return *instance;
}


