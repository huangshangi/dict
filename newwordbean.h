#ifndef NEWWORDBEAN_H
#define NEWWORDBEAN_H
#include <QString>

//数据库->生词本
class newWordBean
{
public:
    newWordBean();

    newWordBean(QString name,QString groupName,QString soundMark,QString explain,QString dateAdd);

    QString getName() const;
    void setName(const QString &value);

    QString getGroupName() const;
    void setGroupName(const QString &value);

    QString getSoundMark() const;
    void setSoundMark(const QString &value);

    QString getExplain() const;
    void setExplain(const QString &value);

    QString getDateAdd() const;
    void setDateAdd(const QString &value);

private:
    QString name;//单词
    QString groupName;//单词分组
    QString soundMark;//单词音标
    QString explain;//单词释义
    QString dateAdd;//单词添加日期
};

#endif // NEWWORDBEAN_H
