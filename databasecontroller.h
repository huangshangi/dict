#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H
#include "newwordbean.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMutex>
#include <QMutexLocker>
#include <QVariant>
#include <QDebug>
class databaseController
{
public:
    databaseController();

    databaseController(QSqlDatabase&database);

    static databaseController& getInstance(QSqlDatabase&database);

    static databaseController& getInstance();

    void initTable();

    bool IsTableExist(QString table);



    int insertNewWord(newWordBean bean);

    int deleteNewWord(QString&name);

    int changeGroupName(QString&oldname,QString&groupName);

    int changeGroupNameByName(QString&, QString&dictName);

    int changeSoundMark(QString&name,QString&soundMark);

    int changeExplain(QString&name,QString&explain);

    int updateNewword(newWordBean bean);

    int deleteGroup(QString&name);

    int addGroup(QString&name);

    newWordBean getNewWordByName(QString &name);

    //获取单词本组
    QList<QString> getGroups();

    //按照时间降序排列
    QList<newWordBean> getListOrderDatedesc(QString group=NULL,QString keyword="");
    //按照时间升序排序
    QList<newWordBean> getListOrderDateasc(QString group=NULL,QString keyword="");
    //按照字母A-Z排序
    QList<newWordBean> getListOrderWordAZ(QString group=NULL,QString keyword="");
    //按照字母Z-A排序
    QList<newWordBean> getListOrderWordZA(QString group=NULL,QString keyword="");
    //按照复习进度快-慢
    QList<newWordBean> getListOrderReviewFS(QString group=NULL,QString keyword="");
    //按照复习进度慢-快
    QList<newWordBean> getListOrderReviewSF(QString group=NULL,QString keyword="");
    //随机排序
    QList<newWordBean> getListOrderRandom(QString group=NULL,QString keyword="");

private:
    static QMutex mutex;
    static databaseController*instance;
    QSqlDatabase database;
    //获取操作对象
    QSqlQuery getSqlQuery();

    //查询newword
    QList<newWordBean>getList(QString &sql);
};

#endif // DATABASECONTROLLER_H
