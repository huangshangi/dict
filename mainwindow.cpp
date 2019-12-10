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

    hideTranWidget();
    showNoteTabbar(0);
    ui->tab_note_list_listwidget->setContextMenuPolicy(Qt::CustomContextMenu);
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

void MainWindow::updateTran(tranBean bean)
{

    if(ui->tran_checkbox->isChecked()){
        ui->tran_edit_to->setText(bean.getSrc()+"\n"+bean.getContent());
    }else{
        ui->tran_edit_to->setText(bean.getContent());
    }


}

//在输入框无内容时隐藏组件
void MainWindow::hideTranWidget()
{
    ui->tran_label_word->hide();
    ui->tran_button_clear->hide();
    ui->tran_button_copy->hide();
    ui->tran_button_pron->hide();
    ui->tran_checkbox->hide();
}

//在输入框有内容时展示组价
void MainWindow::showTranWidget()
{
    ui->tran_label_word->show();
    ui->tran_button_clear->show();
    ui->tran_button_copy->show();
    ui->tran_button_pron->show();
    ui->tran_checkbox->show();
}

void MainWindow::showNoteTabbar(int index)
{
    //隐藏所有布局
    ui->dict_tarbar_widgetedWidget->setCurrentIndex(index);


}

void MainWindow::tab_note_list_delete()
{
    QSqlDatabase database=ConnectPool::openConnection();


    databaseController controller=databaseController::getInstance(database);

    int result=QMessageBox::question(this,"提示","确定删除该单词吗?","确定","取消");
    if(result)
        return;
    QList<QListWidgetItem*>items=ui->tab_note_list_listwidget->selectedItems();
    foreach (QListWidgetItem* item, items) {
        QWidget*widget=ui->tab_note_list_listwidget->itemWidget(item);
        QLabel*label=(QLabel*)widget->children().at(2);
        QString s=label->text();
        controller.deleteNewWord(s);

    }
    ConnectPool::closeConnection(database);
}

void MainWindow::tab_note_list_edit()
{
    QList<QListWidgetItem*>items=ui->tab_note_list_listwidget->selectedItems();

    foreach (QListWidgetItem*item, items) {
        QWidget*widget=ui->tab_note_list_listwidget->itemWidget(item);
        QLabel*label=(QLabel*)widget->children().at(2);
        dict_edit* bean=new dict_edit(this,label->text());

        bean->show();
    }


}

void MainWindow::tab_note_list_move()
{

}

void MainWindow::tab_note_list_noreview()
{

}

void MainWindow::tab_note_list_setting_group()
{
    groupmanagment *managment=new groupmanagment(this);
    managment->show();
}

void MainWindow::tab_note_list_setting_add()
{

}

void MainWindow::tab_note_list_setting_setting()
{

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
    dictbean=dictBean::fromJson(s);
    updateDict(dictbean);

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
    QNetworkAccessManager*manger=networkController->getUrl(dictbean.getAudio().toUtf8().data());
    qDebug()<<dictbean.getAudio();
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
    if(length==0){
        hideTranWidget();
        return;
    }else{
        showTranWidget();
    }

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

void MainWindow::on_tran_button_tran_clicked()
{
    //进行翻译
    QString value=ui->tran_edit_from->toPlainText();
    //将翻译内容进行翻译
    QString res="{\"src\": \"私は七瀬です\", \"content\": \"我是七濑\", \"audio\": \"https://dict.youdao.com/dictvoice?audio=私は七瀬です&le=jap\"}";
    //connect(updateTran())
    tranbean=tranBean::fromJson(res);

    updateTran(tranbean);

}

void MainWindow::on_tran_checkbox_clicked(bool checked)
{
    updateTran(tranbean);
}

void MainWindow::on_tran_button_pron_clicked()
{
    NetworkController *networkController=new NetworkController;
    QNetworkAccessManager*manger=networkController->getUrl(tranbean.getAudio().toUtf8().data());

    connect(manger,SIGNAL(finished(QNetworkReply*)), this, SLOT(playAudio(QNetworkReply*)));
}

void MainWindow::on_dict_button_add_clicked()
{
    //将单词加入生词本
    QSqlDatabase database=ConnectPool::openConnection();


    databaseController controller=databaseController::getInstance(database);
    newWordBean bean;

    QObjectList list=ui->scrollAreaWidgetContents->children();
    QString explain;
    for(int i=1;i<list.size();i++){
        QLabel*label=(QLabel*)list.at(i);
        explain+=label->text()+"\n";
    }
    bean.setName(ui->dict_title->text());
    bean.setGroupName("");
    bean.setSoundMark("");
    bean.setExplain(explain);
    bean.setDateAdd("2019-12-08");


    controller.insertNewWord(bean);


    ConnectPool::closeConnection(database);
}

void MainWindow::on_tabWidget_main_tabBarClicked(int index)
{
    //点击单词本
    if(index==2){
        QSqlDatabase database=ConnectPool::openConnection();
        databaseController controller=databaseController::getInstance(database);
        QList<newWordBean>list=controller.getListOrderDatedesc();
        ui->tab_note_list_listwidget->clear();
        for(int i=0;i<list.size();i++){
            QListWidgetItem *item=new QListWidgetItem;

            QWidget*widget=new QWidget;
            QHBoxLayout*hLayout=new QHBoxLayout;
            newWordBean bean=list.at(i);
            QLabel*label_id=new QLabel;
            QLabel*label_title=new QLabel;
            QLabel*label_content=new QLabel;
            label_id->setText(QString::number(i+1));
            label_title->setText(bean.getName());
            label_content->setText(bean.getExplain().replace("\n",""));
            hLayout->addWidget(label_id,1,Qt::AlignLeft);
            hLayout->addWidget(label_title,1,Qt::AlignLeft);
            hLayout->addWidget(label_content,12,Qt::AlignLeft);

            hLayout->addStretch();
            widget->setLayout(hLayout);
            QSize size=item->sizeHint();
            item->setSizeHint(QSize(size.width(),56));
            ui->tab_note_list_listwidget->addItem(item);
            widget->setSizeIncrement(size.width(),56);
            ui->tab_note_list_listwidget->setItemWidget(item,widget);

        }




        //添加 列表 右键菜单
        QMenu*menu=new QMenu(this);
        QMenu*menuMove=new QMenu(this);
        menuMove->setTitle("移动到");
        QAction*action_dele=new QAction("删除单词",this);
        QAction*action_edit=new QAction("编辑单词",this);
        QAction*action_noreview=new QAction("不再复习",this);
        menu->addAction(action_dele);
        menu->addAction(action_edit);
        menu->addAction(action_noreview);
        menu->addMenu(menuMove);
        QAction*action_move_1=new QAction("未分组",this);
        menuMove->addAction(action_move_1);
        connect(ui->tab_note_list_listwidget,&QWidget::customContextMenuRequested,[=](const QPoint &pos)
           {
               menu->exec(QCursor::pos());
           });

        // 为动作设置信号槽

        connect(action_dele, SIGNAL(triggered()),this,SLOT(tab_note_list_delete()));

        connect(action_edit,SIGNAL(triggered()),this,SLOT(tab_note_list_edit()));

        connect(action_edit,SIGNAL(triggered()),this,SLOT(tab_note_list_move()));

        connect(action_edit,SIGNAL(triggered()),this,SLOT(tab_note_list_noreview()));


    }
}

void MainWindow::on_tab_note_button_list_clicked()
{
    ui->dict_stackedWidget->setCurrentIndex(0);
    showNoteTabbar(0);
}

void MainWindow::on_tab_note_button_card_clicked()
{
    ui->dict_stackedWidget->setCurrentIndex(1);
    showNoteTabbar(1);
    //进行数据的获取
    int index=0;
    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);

    QList<newWordBean>list=controller.getListOrderRandom();
    int size=list.size();

    newWordBean bean=list.at(index);
    ui->tab_note_card_count->setText(QString::number(index+1)+"/"+QString::number(size));
    ui->tab_note_card_title->setText(bean.getName());
    ui->tab_note_card_expalin->setText(bean.getExplain());
    ui->tab_note_card_pre->show();
    ui->tab_note_card_next->show();
    ui->tab_note_card_button->show();
    ui->tab_note_card_expalin->hide();
    if(index+1==size)
         ui->tab_note_card_next->hide();

   if(index==0)
         ui->tab_note_card_pre->hide();




    ConnectPool::closeConnection(database);
}

void MainWindow::on_tab_note_button_review_clicked()
{
    ui->dict_stackedWidget->setCurrentIndex(2);
    showNoteTabbar(2);
}



void MainWindow::on_tab_note_card_pre_clicked()
{
    int index=ui->tab_note_card_count->text().left(ui->tab_note_card_count->text().indexOf('/')).toInt();
    index-=1;

    //判断未实现
}

void MainWindow::on_tab_note_card_button_clicked()
{
    ui->tab_note_card_button->hide();

    ui->tab_note_card_expalin->show();
}

void MainWindow::on_tab_note_card_next_clicked()
{
    int index=ui->tab_note_card_count->text().left(ui->tab_note_card_count->text().indexOf('/')).toInt();
    index+=1;

    //判断未实现
}


void MainWindow::on_tab_note_list_button_setting_clicked()
{
    QMenu*menu=new QMenu(this);

    QAction*action_group=new QAction("分组管理",this);
    QAction*action_add=new QAction("添加单词",this);
    QAction*action_setting=new QAction("偏好设置",this);
    menu->addAction(action_group);
    menu->addAction(action_add);
    menu->addAction(action_setting);

    connect(action_group, SIGNAL(triggered()),this,SLOT(tab_note_list_setting_group()));
    connect(action_add, SIGNAL(triggered()),this,SLOT(tab_note_list_setting_add()));
    connect(action_setting, SIGNAL(triggered()),this,SLOT(tab_note_list_setting_setting()));

    QPoint p=QPoint(ui->tab_note_list_button_setting->x(),
                    ui->tab_note_list_button_setting->y()+ui->tab_note_list_button_setting->height());

    menu->exec(ui->tab_note_list_button_setting->mapToGlobal(ui->tab_note_list_button_setting->mapFromParent(p)));
}
