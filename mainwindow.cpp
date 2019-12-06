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

    NetworkController *networkController=new NetworkController;
    QNetworkAccessManager*manger=networkController->getUrl("https://www.youdao.com/w/jap/テスト");
    QMetaObject::Connection con = QObject::connect(manger,
            SIGNAL(finished(QNetworkReply*)), dictTab, SLOT(requestFinished(QNetworkReply*)));
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
        qDebug()<<ll.size();
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
                qDebug()<<ss;
            }


        }
    }
    ui->scrollArea_simp->widget()->setLayout(layout);
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
