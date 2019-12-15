#ifndef SETTINGS_H
#define SETTINGS_H

#include <QString>
#include <config.h>
#include <QMutex>
#include <QMutexLocker>
class settings
{
public:


    static settings* getInstance();

    static void writeTo(settings*);//将内容写回

    static void update();

    QString getFrom() const;
    void setFrom(const QString &value);

    QString getTo() const;
    void setTo(const QString &value);

    QString getSource() const;
    void setSource(const QString &value);

    bool getFont() const;
    void setFont(bool value);

    bool getStartup_bootup() const;
    void setStartup_bootup(bool value);

    bool getStartup_min() const;
    void setStartup_min(bool value);

    bool getMainwindow_first() const;
    void setMainwindow_first(bool value);

    bool getMainwindow_min() const;
    void setMainwindow_min(bool value);

    bool getRightClick_add() const;
    void setRightClick_add(bool value);

    bool getBrowse_audio() const;
    void setBrowse_audio(bool value);

    int getHistory() const;

    void setHistory(int value);

    bool getReview_remind() const;
    void setReview_remind(bool value);

    bool getReview_audio() const;
    void setReview_audio(bool value);

    bool getReview_add() const;
    void setReview_add(bool value);

    bool getFind_add() const;
    void setFind_add(bool value);

    bool getPlay_show() const;
    void setPlay_show(bool value);

    int getReview_max() const;
    void setReview_max(int value);

    QString getDefault_note() const;
    void setDefault_note(const QString &value);

private:
    settings();


    QString from;
    QString to;
    QString source;
    bool font;//字体大小
    bool startup_bootup;//开机时自动启动
    bool startup_min;//启动后最小化到系统托盘
    bool mainwindow_first;//主窗口总在最前
    bool mainwindow_min;//窗口关闭时最小化到系统托盘
    bool rightClick_add;//把使用有道词典添加到鼠标右键菜单

    bool browse_audio;//单词浏览时自动发音
    int history;//选择查询历史记录条数

    bool review_remind;//在系统任务栏提醒复习
    bool review_audio;//单词复习时自动发音
    bool review_add;//添加单词时默认加入复习计划
    bool find_add;//查过的单词自动加入单词本
    bool play_show;//单词播放时直接显示释义
    int review_max;//每日进入复习流程的单词上限
    QString default_note;

    static settings* obj;
    static QMutex mutex;

};

#endif // SETTINGS_H
