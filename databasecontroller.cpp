#include "databasecontroller.h"

QMutex databaseController::mutex;
databaseController* databaseController::instance=NULL;


databaseController::databaseController()
{


}

databaseController::databaseController(QSqlDatabase &database)
{
    this->database=database;

    if(!IsTableExist("groups")||!IsTableExist("newWord"))
        initTable();

}

databaseController &databaseController::getInstance(QSqlDatabase &database)
{
    if(instance==NULL){
        QMutexLocker locaker(&mutex);
        if(instance==NULL){
            instance=new databaseController(database);
        }

    }
    return *instance;
}

databaseController &databaseController::getInstance()
{
    if(instance==NULL){
        QMutexLocker locaker(&mutex);
        if(instance==NULL){
            instance=new databaseController();
        }

    }
    return *instance;
}

void databaseController::initTable()
{

     QSqlQuery sqlQuery(database);

    sqlQuery.exec("create table groups (groupName varchar(50));");
    sqlQuery.exec("create table newWord(name varchar(50) not null,groupName varchar(50),soundMask varchar(50),explain varchar(250),"
                  "dateAdd date not null);");


}

bool databaseController::IsTableExist(QString table)
{

    QSqlQuery sqlQuery(database);

    QString sql = QString("select count(*) from sqlite_master where type = 'table' and name='%1'").arg(table);
    sqlQuery.exec(sql);
    sqlQuery.next();
    int a=sqlQuery.value(0).toInt();

    return sqlQuery.value(0).toInt();


}

int databaseController::insertNewWord(newWordBean bean)
{
    QSqlQuery sqlQuery=getSqlQuery();

    QString sql="insert into newWord(name,groupName,soundMark,explain,dateAdd) values("
                ":name,:groupName,:soundMark,:explain,:dateAdd);";

    sqlQuery.prepare(sql);
    sqlQuery.bindValue(":name",QVariant(bean.getName()));
    sqlQuery.bindValue(":groupName",QVariant(bean.getGroupName()));
    sqlQuery.bindValue(":soundMark",QVariant(bean.getSoundMark()));
    sqlQuery.bindValue(":explain",QVariant(bean.getExplain()));
    sqlQuery.bindValue(":dateAdd",QVariant(bean.getDateAdd()));
    return sqlQuery.exec();





}

int databaseController::deleteNewWord(QString &name)
{
    QSqlQuery sqlQuery=getSqlQuery();

    QString sql="delete from newWord where name=?;";

    sqlQuery.prepare(sql);
    sqlQuery.addBindValue(name);

    return sqlQuery.exec();
}

int databaseController::changeGroupName(QString &name, QString &groupName)
{
    QSqlQuery sqlQuery=getSqlQuery();

    QString sql="update newWord set groupName=? where groupName=?;";
    sqlQuery.prepare(sql);
    sqlQuery.addBindValue(groupName);
    sqlQuery.addBindValue(name);
    sqlQuery.exec();

    sql="update groups set groupName=? where groupName=?; ";
    sqlQuery.prepare(sql);
    sqlQuery.addBindValue(groupName);
    sqlQuery.addBindValue(name);
    return sqlQuery.exec();
}

int databaseController::changeGroupNameByName(QString&groupName,QString &dictName)
{
    QSqlQuery sqlQuery=getSqlQuery();
    QString sql="update newWord set groupName=? where name=?;";
    sqlQuery.prepare(sql);
    sqlQuery.addBindValue(groupName);
    sqlQuery.addBindValue(dictName);
    return sqlQuery.exec();
}

int databaseController::changeSoundMark(QString &name, QString &soundMark)
{
    QSqlQuery sqlQuery=getSqlQuery();

    QString sql="update newWord set soundMark=? where name=?;";
    sqlQuery.prepare(sql);
    sqlQuery.addBindValue(soundMark);
    sqlQuery.addBindValue(name);

    return sqlQuery.exec();
}

int databaseController::changeExplain(QString &name, QString &explain)
{
    QSqlQuery sqlQuery=getSqlQuery();

    QString sql="update newWord set explain=? where name=?;";
    sqlQuery.prepare(sql);
    sqlQuery.addBindValue(explain);
    sqlQuery.addBindValue(name);

    return sqlQuery.exec();
}

int databaseController::updateNewword(newWordBean bean)
{

    QSqlQuery sqlQuery=getSqlQuery();

    QString sql="update newWord set groupName=?,soundMark=?,explain=?  where name=?;";
    sqlQuery.prepare(sql);
    sqlQuery.addBindValue(bean.getGroupName());
    sqlQuery.addBindValue(bean.getSoundMark());
    sqlQuery.addBindValue(bean.getExplain());
    sqlQuery.addBindValue(bean.getName());


    return sqlQuery.exec();
}

//待优化
int databaseController::deleteGroup(QString &name)
{
    QSqlQuery sqlQuery=getSqlQuery();



    QString sql="update newWord set groupName='' where groupName=?;";

    sqlQuery.prepare(sql);
    sqlQuery.addBindValue(name);
    sqlQuery.exec();

    sql="delete from groups where groupName=?;";
    sqlQuery.prepare(sql);
    sqlQuery.addBindValue(name);



    return sqlQuery.exec();
}

int databaseController::addGroup(QString &name)
{
    QString sql="insert into groups (groupName) values(?);";
    QSqlQuery sqlQuery=getSqlQuery();
    sqlQuery.prepare(sql);
    sqlQuery.addBindValue(name);

    return sqlQuery.exec();
}

newWordBean databaseController::getNewWordByName(QString &name)
{

    QString sql=QString("select * from newWord where name='%1';").arg(name);


    QList<newWordBean>list=getList(sql);
    if(list.size()>0)
        return list.at(0);
    else
        return newWordBean();

}

QList<QString> databaseController::getGroups()
{
    QList<QString>list;
    QString sql="select distinct groupName from groups;";
    QSqlQuery sqlQuery=getSqlQuery();
    sqlQuery.prepare(sql);
    sqlQuery.exec();
    while(sqlQuery.next()){
        list.append(sqlQuery.value(0).toString());
    }
    return list;
}

QList<newWordBean> databaseController::getListOrderDatedesc(QString group,QString keyword)
{ 
    QString add="";
    if(!group.isEmpty())//group 为null ""
        add="where name like '%"+keyword+"%'"+" and groupName='"+group+"'";
    else if(!group.isNull())//group不为null
        add="where name like '%"+keyword+"%'"+" and groupName is null or groupName==''";
    else
        add="where name like '%"+keyword+"%'";
    QString sql=QString("select *from newWord %1 order by dateAdd desc;").arg(add);

    return getList(sql);
}

QList<newWordBean> databaseController::getListOrderDateasc(QString group,QString keyword)
{

    QString add="";
    if(!group.isEmpty())//group 为null ""
        add="where name like '%"+keyword+"%'"+" and groupName='"+group+"'";
    else if(!group.isNull())//group不为null
        add="where name like '%"+keyword+"%'"+" and groupName is null or groupName==''";
    else
        add="where name like '%"+keyword+"%'";
    QString sql=QString("select *from newWord %1 order by dateAdd asc;").arg(add);

    return getList(sql);
}

QList<newWordBean> databaseController::getListOrderWordAZ(QString group,QString keyword)
{

    QString add="";
    if(!group.isEmpty())//group 为null ""
        add="where name like '%"+keyword+"%'"+" and groupName='"+group+"'";
    else if(!group.isNull())//group不为null
        add="where name like '%"+keyword+"%'"+" and groupName is null or groupName==''";
    else
        add="where name like '%"+keyword+"%'";
    QString sql=QString("select *from newWord %1 order by name asc;").arg(add);
    return getList(sql);
}

QList<newWordBean> databaseController::getListOrderWordZA(QString group,QString keyword)
{

    QString add="";
    if(!group.isEmpty())//group 为null ""
        add="where name like '%"+keyword+"%'"+" and groupName='"+group+"'";
    else if(!group.isNull())//group不为null
        add="where name like '%"+keyword+"%'"+" and groupName is null or groupName==''";
    else
        add="where name like '%"+keyword+"%'";
    QString sql=QString("select *from newWord %1 order by name desc;").arg(add);
    return getList(sql);
}

QList<newWordBean> databaseController::getListOrderReviewFS(QString group,QString keyword)
{

}

QList<newWordBean> databaseController::getListOrderReviewSF(QString group,QString keyword)
{

}

QList<newWordBean> databaseController::getListOrderRandom(QString group,QString keyword)
{
    QString add="";
    if(!group.isEmpty())//group 为null ""
        add="where name like '%"+keyword+"%'"+" and groupName='"+group+"'";
    else if(!group.isNull())//group不为null
        add="where name like '%"+keyword+"%'"+" and groupName is null or groupName==''";
    else
        add="where name like '%"+keyword+"%'";
    QString sql=QString("select *from newWord %1 order by random();").arg(add);


    return getList(sql);
}

QSqlQuery databaseController::getSqlQuery()
{

    databaseController obj=databaseController::getInstance();

    QSqlQuery sqlQuery(obj.database);

    return sqlQuery;
}

QList<newWordBean> databaseController::getList(QString &sql)
{
    QSqlQuery sqlQuery=getSqlQuery();

    QList<newWordBean>list;

    sqlQuery.prepare(sql);
    sqlQuery.exec();
    while(sqlQuery.next()){
        newWordBean bean;
        bean.setName(sqlQuery.value(0).toString());
        bean.setGroupName(sqlQuery.value(1).toString());
        bean.setSoundMark(sqlQuery.value(2).toString());
        bean.setExplain(sqlQuery.value(3).toString());
        bean.setDateAdd(sqlQuery.value(4).toString());
        list.append(bean);
    }
    return list;
}

