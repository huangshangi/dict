#include "settings.h"

settings* settings::obj;
QMutex settings::mutex;
settings::settings()
{

    Config config;
    QString path="dict";
    setFrom(config.get(path,"from").toString());
    setTo(config.get(path,"to").toString());
    setSource(config.get(path,"source").toString());

    path="normal";
    setFont(config.get(path,"font").toBool());
    setStartup_bootup(config.get(path,"startup-bootup").toBool());
    setStartup_min(config.get(path,"startup-min").toBool());
    setMainwindow_first(config.get(path,"mainwindow-first").toBool());
    setMainwindow_min(config.get(path,"mainwindow-min").toBool());
    setRightClick_add(config.get(path,"rightClick-add").toBool());


    path="content";
    setBrowse_audio(config.get(path,"browse-audio").toBool());
    setHistory(config.get(path,"history").toInt());

    path="note";
    setReview_remind(config.get(path,"review-remind").toBool());
    setReview_audio(config.get(path,"review-audio").toBool());
    setReview_add(config.get(path,"review-add").toBool());
    setFind_add(config.get(path,"find-add").toBool());
    setPlay_show(config.get(path,"play-show").toBool());
    setReview_max(config.get(path,"review-max").toInt());
    setDefault_note(config.get(path,"default-note").toString());



}




settings* settings::getInstance()
{
    if(obj==NULL){
        QMutexLocker locker(&mutex);
        if(obj==NULL)
            obj=new settings();
    }

    return obj;
}

void settings::writeTo(settings *s)
{
    static Config config;
    QString path="dict";
    config.set(path,"from",s->getFrom());
    config.set(path,"to",s->getTo());
    config.set(path,"source",s->getSource());

    path="normal";
    config.set(path,"font",s->getFont());
    config.set(path,"startup-bootup",s->getStartup_bootup());
    config.set(path,"startup-min",s->getStartup_min());
    config.set(path,"mainwindow-first",s->getMainwindow_first());
    config.set(path,"mainwindow-min",s->getMainwindow_min());
    config.set(path,"rightClick-add",s->getRightClick_add());



    path="content";
    config.set(path,"browse-audio",s->getBrowse_audio());
    config.set(path,"history",s->getHistory());


    path="note";
    config.set(path,"review-remind",s->getReview_remind());
    config.set(path,"review-audio",s->getReview_audio());
    config.set(path,"review-add",s->getReview_add());
    config.set(path,"find-add",s->getFind_add());
    config.set(path,"play-show",s->getPlay_show());
    config.set(path,"review-max",s->getReview_max());
    config.set(path,"default-note",s->getDefault_note());



}

void settings::update()
{
    obj=new settings();
}

QString settings::getFrom() const
{
    return from;
}

void settings::setFrom(const QString &value)
{
    from = value;
}

QString settings::getTo() const
{
    return to;
}

void settings::setTo(const QString &value)
{
    to = value;
}

QString settings::getSource() const
{
    return source;
}

void settings::setSource(const QString &value)
{
    source = value;
}

bool settings::getFont() const
{
    return font;
}

void settings::setFont(bool value)
{
    font = value;
}

bool settings::getStartup_bootup() const
{
    return startup_bootup;
}

void settings::setStartup_bootup(bool value)
{
    startup_bootup = value;
}

bool settings::getStartup_min() const
{
    return startup_min;
}

void settings::setStartup_min(bool value)
{
    startup_min = value;
}

bool settings::getMainwindow_first() const
{
    return mainwindow_first;
}

void settings::setMainwindow_first(bool value)
{
    mainwindow_first = value;
}

bool settings::getMainwindow_min() const
{
    return mainwindow_min;
}

void settings::setMainwindow_min(bool value)
{
    mainwindow_min = value;
}

bool settings::getRightClick_add() const
{
    return rightClick_add;
}

void settings::setRightClick_add(bool value)
{
    rightClick_add = value;
}

bool settings::getBrowse_audio() const
{
    return browse_audio;
}

void settings::setBrowse_audio(bool value)
{
    browse_audio = value;
}

int settings::getHistory() const
{
    return history;
}

void settings::setHistory(int value)
{
    history = value;
}

bool settings::getReview_remind() const
{
    return review_remind;
}

void settings::setReview_remind(bool value)
{
    review_remind = value;
}

bool settings::getReview_audio() const
{
    return review_audio;
}

void settings::setReview_audio(bool value)
{
    review_audio = value;
}

bool settings::getReview_add() const
{
    return review_add;
}

void settings::setReview_add(bool value)
{
    review_add = value;
}

bool settings::getFind_add() const
{
    return find_add;
}

void settings::setFind_add(bool value)
{
    find_add = value;
}

bool settings::getPlay_show() const
{
    return play_show;
}

void settings::setPlay_show(bool value)
{
    play_show = value;
}

int settings::getReview_max() const
{
    return review_max;
}

void settings::setReview_max(int value)
{
    review_max = value;
}

QString settings::getDefault_note() const
{
    return default_note;
}

void settings::setDefault_note(const QString &value)
{
    default_note = value;
}
