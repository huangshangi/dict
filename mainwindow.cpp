#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec* codec = QTextCodec::codecForName("GB2312");
    ui->setupUi(this);
    ui->tabWidget_main->tabBar()->setStyle(new CustomTabStyle);
    ui->tabWidget_dict->tabBar()->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateDict(dictBean bean)
{
   //对简明翻译进行更新
    QVBoxLayout *layout=new QVBoxLayout;
    QList<dict_simpBean>list=bean.getList();
    for(int i=0;i<list.size();i++){
        dict_simpBean bean=list.at(i);
        QLabel*label=new QLabel;
        label->setText(bean.getVoc_pro());
        layout->addWidget(label);
        QList<QMap<QString,QString> >ll=bean.getList();

        for(int j=0;j<ll.size();j++){
            QMap<QString,QString>map=ll.at(j);

            QLabel*labelTitle=new QLabel;
            QMap<QString,QString>::const_iterator iteratorTitle=map.find("sense-title");

            if(iteratorTitle!=map.end()){
                QString s=iteratorTitle.value();
                labelTitle->setText(s);
                layout->addWidget(labelTitle);
            }


            QLabel*labelContent=new QLabel;
            QMap<QString,QString>::const_iterator iteratorContent=map.find("sense-ex");
            if(iteratorContent!=map.end()){
                QString ss=iteratorContent.value();
                labelContent->setText(ss);
                layout->addWidget(labelContent);

            }


        }
    }
    layout->addStretch();
    ui->scrollArea_simp->widget()->setLayout(layout);

    //对网络释义进行更新
    QVBoxLayout *layout_web=new QVBoxLayout;
    QList<dict_webBean>list_web=bean.getList_web();
    for(int i=0;i<list_web.size();i++){
        dict_webBean bean=list_web.at(i);
        QMap<QString,QString> map=bean.getMap();

        QMap<QString,QString>::const_iterator iteratorTitle=map.find("title");
        QMap<QString,QString>::const_iterator iteratorContent=map.find("content");
        QLabel *labelTitle=new QLabel;
        QLabel *labelContent=new QLabel;

        if(iteratorTitle!=map.end()){
            labelTitle->setText(iteratorTitle.value());
            layout_web->addWidget(labelTitle);
        }

        if(iteratorContent!=map.end()){
            labelContent->setText(iteratorContent.value());

            layout_web->addWidget(labelContent);
        }

    }
    layout_web->addStretch();
    ui->scrollArea_web->widget()->setLayout(layout_web);


    //对短语进行更新
    QVBoxLayout *layout_phrase=new QVBoxLayout;
    QList<dict_phraseBean>list_phrase=bean.getList_phrase();

    for(int i=0;i<list_phrase.size();i++){
        dict_phraseBean bean=list_phrase.at(i);
        QMap<QString,QString> map=bean.getMap();

        QMap<QString,QString>::const_iterator iteratorTitle=map.find("title");
        QMap<QString,QString>::const_iterator iteratorContent=map.find("content");
        QLabel *labelTitle=new QLabel;
        QLabel *labelContent=new QLabel;

        if(iteratorTitle!=map.end()){
            labelTitle->setText(iteratorTitle.value());

            layout_phrase->addWidget(labelTitle);
        }

        if(iteratorContent!=map.end()){
            labelContent->setText(iteratorContent.value());
            layout_phrase->addWidget(labelContent);
        }

    }
    layout_phrase->addStretch();
    ui->scrollArea_phrase->widget()->setLayout(layout_phrase);


    //对例句进行更新
    QVBoxLayout *layout_example=new QVBoxLayout;
    QList<dict_exampleBean>list_example=bean.getList_example();

    for(int i=0;i<list_example.size();i++){
        dict_exampleBean bean=list_example.at(i);
        QMap<QString,QString> map=bean.getMap();

        QMap<QString,QString>::const_iterator iteratorTitle=map.find("title");
        QMap<QString,QString>::const_iterator iteratorContent=map.find("content");
        QLabel *labelTitle=new QLabel;
        QLabel *labelContent=new QLabel;

        if(iteratorTitle!=map.end()){
            labelTitle->setText(iteratorTitle.value());
            labelTitle->setGeometry(10,10,91,31);
            layout_example->addWidget(labelTitle);
        }

        if(iteratorContent!=map.end()){
            labelContent->setText(iteratorContent.value());
            labelContent->setGeometry(10,10,91,31);
            layout_example->addWidget(labelContent);

        }

    }
    layout_example->addStretch();
   ui->scrollArea_example->widget()->setLayout(layout_example);

}

void MainWindow::playAudio(QNetworkReply *reply)
{

    QByteArray array=reply->readAll();

    QFile file("C:\\Users\\hzh17\\Desktop\\temp.mp3");
    if(file.open(QIODevice::WriteOnly)){
        QDataStream stream(&file);
        stream<<array;
    }

    file.close();
    QMediaPlayer* player = new QMediaPlayer;

    player->setMedia(QUrl::fromLocalFile(file.fileName()));
    player->setVolume(30);
    player->play();

    
}



void MainWindow::on_dict_button_back_clicked()
{
    ui->tabWidget_dict->setCurrentIndex(0);
}


//点击查询按钮
void MainWindow::on_dict_find_clicked()
{
    ui->tabWidget_dict->setCurrentIndex(1);
    //进行网络操作,查询到数据
    QByteArray data=QByteArray("{\"keyword\": \"あいさつ\", \"title\": \"あいさつ①【挨拶】\", \"list\": [{\"voc_pro\": \"[名·自サ]\", \"list\": [{\"sense-title\": \"问候，打招呼，致意\", \"sense-ex\": \"例证:\nあいさつを交わす\n互相致意\"}, {\"sense-title\": \"(初次见面)自我介绍\"}, {\"sense-title\": \"致词，讲话\"}, {\"sense-title\": \"(书信的首尾)问候，祝愿\"}, {\"sense-title\": \"拜访，告别，问候\"}]}], \"list_web\": [{\"title\": \"あいさつ\", \"content\": \"居然用“妖猫”打招呼，白哉小子，难得我说要来陪你玩呢。 解说：挨拶（あいさつ）：寒暄语。与人见面或分别等时的寒暄及其礼貌动作。\"}], \"list_phrase\": [{\"title\": \"ご挨拶\", \"content\": \"讲话\"}, {\"title\": \"开演挨拶\", \"content\": \"フリオ・キリコ\"}, {\"title\": \"舞台挨拶\", \"content\": \"ボクたちの交换日记\"}, {\"title\": \"闭会挨拶\", \"content\": \"神戸会場より中継\"}, {\"title\": \"舞台挨拶映像集\", \"content\": \"プレミア上映会・初日舞台挨拶\"}, {\"title\": \"舞台挨拶のみ\", \"content\": \"田中美佐子\"}, {\"title\": \"管理者挨拶\", \"content\": \"リハビリ室見学・仕事内容説明\"}], \"list_example\": [{\"title\": \"初日舞台挨拶决定！！\", \"content\": \"※初日舞台挨拶は満席となりました。\"}, {\"title\": \"映画『白夜行』公开初日舞台挨拶（ 堀北真希...\", \"content\": \"それにしても、堀北真希さんもよく、この映画の ...\"}, {\"title\": \"校长挨拶、行事予定、概要、学级の活动绍介等。\", \"content\": \"学校のキャッチフレーズ、各学级の活动、学校の最新ニュース等。\"}]}");
    QString s=data;
    dictBean bean=dictBean::fromJson(s);
    updateDict(bean);

}

void MainWindow::on_dict_doc_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("选择文件"),
                                                        "F:",
                                                        tr("图片文件(*png *jpg);;"
                                                           "全部本文件(*txt)"));
}

void MainWindow::on_dict_shot_clicked()
{
    Capture* capture=new Capture;
    capture->show();
}

//播放音频
void MainWindow::on_dict_button_pron_clicked()
{
    NetworkController *networkController=new NetworkController;
    QNetworkAccessManager*manger=networkController->getUrl("https://dict.youdao.com/dictvoice?audio=%E3%83%86%E3%82%B9%E3%83%88&le=jap");
    connect(manger,SIGNAL(finished(QNetworkReply*)), this, SLOT(playAudio(QNetworkReply*)));

}

void MainWindow::on_dict_button_find_clicked()
{

}

void MainWindow::on_tran_edit_from_textChanged()
{
    //设置文字字数变化
    QString s=ui->tran_edit_from->toPlainText();
    int length=s.length();
    QString lengthS=QString::number(length);
    ui->tran_label_word->setText(lengthS+"/"+QString::number(TRAN_FROM_MAX_LENGTH));

    //最大字数限制
    int maxLength=TRAN_FROM_MAX_LENGTH;
    if(length>maxLength){
        QTextCursor textCursor=ui->tran_edit_from->textCursor();
        s.remove(maxLength,length-maxLength);
        ui->tran_edit_from->setText(s);
        textCursor.setPosition(maxLength);
        ui->tran_edit_from->setTextCursor(textCursor);
    }
}

void MainWindow::on_tran_button_clear_clicked()
{
    //清空翻译框
    ui->tran_edit_from->setText("");
}
