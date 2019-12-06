#include "dictbean.h"

dictBean::dictBean()
{

}

dictBean dictBean::fromJson(QString &json)
{
    QByteArray data=json.toUtf8();
    QJsonParseError parseError;
    dictBean bean;
    QJsonDocument document=QJsonDocument::fromJson(data,&parseError);
    if(parseError.error==QJsonParseError::NoError&&document.isObject()){

        QJsonObject rootObj=document.object();
        if(rootObj.contains("keyword"))
            bean.setKeyword(rootObj.value("keyword").toString());

        if(rootObj.contains("title"))
            bean.setTitle(rootObj.value("title").toString());

        if(rootObj.contains("audio"))
            bean.setAudio(rootObj.value("audio").toString());

        if(rootObj.contains("list")&&rootObj.value("list").isArray()){
            QJsonArray array=rootObj.value("list").toArray();
            QList<dict_simpBean>list;
            for(int i=0;i<array.size();i++){
                QJsonObject obj=array[i].toObject();
                dict_simpBean simpBean;
                if(obj.contains("voc_pro"))
                    simpBean.setVoc_pro(obj.value("voc_pro").toString());
                QList<QMap<QString,QString>>ll;
                if(obj.contains("list")){
                    QJsonArray array2=obj.value("list").toArray();

                    for(int j=0;j<array2.size();j++){
                        QMap<QString,QString> map;
                        QJsonObject obj2=array2[j].toObject();
                        if(obj2.contains("sense-title"))
                            map.insert("sense-title",obj2.value("sense-title").toString());
                        if(obj2.contains("sense-ex"))
                            map.insert("sense-ex",obj2.value("sense-ex").toString());
                        ll.append(map);
                    }
                }
                simpBean.setList(ll);
                list.append(simpBean);
                bean.setList(list);
            }
        }

        if(rootObj.contains("list_web")){
            QJsonArray array=rootObj.value("list_web").toArray();
            QList<dict_webBean>list;


            for(int i=0;i<array.size();i++){
                dict_webBean bean;
                QJsonObject obj=array[i].toObject();
                if(obj.contains("title"))
                    bean.getMap().insert("title",obj.value("title").toString());

                if(obj.contains("content"))
                    bean.getMap().insert("content",obj.value("content").toString());

                list.append(bean);
            }

            bean.setList_web(list);
        }

        if(rootObj.contains("list_phrase")){
            QJsonArray array=rootObj.value("list_phrase").toArray();
            QList<dict_phraseBean>list;


            for(int i=0;i<array.size();i++){
                dict_phraseBean bean;
                QJsonObject obj=array[i].toObject();
                if(obj.contains("title"))
                    bean.getMap().insert("title",obj.value("title").toString());

                if(obj.contains("content"))
                    bean.getMap().insert("content",obj.value("content").toString());

                list.append(bean);
            }

            bean.setList_phrase(list);
        }
        if(rootObj.contains("list_example")){
            QJsonArray array=rootObj.value("list_example").toArray();
            QList<dict_exampleBean>list;


            for(int i=0;i<array.size();i++){
                dict_exampleBean bean;
                QJsonObject obj=array[i].toObject();
                if(obj.contains("title"))
                    bean.getMap().insert("title",obj.value("title").toString());

                if(obj.contains("content"))
                    bean.getMap().insert("content",obj.value("content").toString());

                list.append(bean);
            }

            bean.setList_example(list);
        }
    }
    return bean;
}

QString dictBean::getKeyword() const
{
    return keyword;
}

void dictBean::setKeyword(const QString &value)
{
    keyword = value;
}

QString dictBean::getTitle() const
{
    return title;
}

void dictBean::setTitle(const QString &value)
{
    title = value;
}

QString dictBean::getAudio() const
{
    return audio;
}

void dictBean::setAudio(const QString &value)
{
    audio = value;
}

QList<dict_simpBean> dictBean::getList() const
{
    return list;
}

void dictBean::setList(const QList<dict_simpBean> &value)
{
    list = value;
}

QList<dict_webBean> dictBean::getList_web() const
{
    return list_web;
}

void dictBean::setList_web(const QList<dict_webBean> &value)
{
    list_web = value;
}

QList<dict_phraseBean> dictBean::getList_phrase() const
{
    return list_phrase;
}

void dictBean::setList_phrase(const QList<dict_phraseBean> &value)
{
    list_phrase = value;
}

QList<dict_exampleBean> dictBean::getList_example() const
{
    return list_example;
}

void dictBean::setList_example(const QList<dict_exampleBean> &value)
{
    list_example = value;
}
