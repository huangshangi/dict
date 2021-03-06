#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //QTextCodec* codec = QTextCodec::codecForName("GB2312");
    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint |Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);

    initQss();
    createSystemTray();
    initSettingMenu();
    hideTranWidget();
    showNoteTabbar(0);
    initKey();//快捷键初始化
    tabBarInit(0);
    installEventFilter();

    s=settings::getInstance();

    ui->tabWidget_dict->tabBar()->hide();
    ui->tab_note_list_listwidget->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->stackedWidget_maxmin->setCurrentIndex(0);
    ui->stackwidget_title->hide();
    ui->tab_note_combox_group->setView(new QListView());
    ui->tab_note_list_button_sort->setView(new QListView());
}

MainWindow::~MainWindow()
{
    delete settingwindow;
    delete setting_menu;
    delete systemTrayIcon;

    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainterPath path;
    QColor color(0, 0, 0, 70);
    path.setFillRule(Qt::WindingFill);
    path.addRect(2, 2, this->width()-4, this->height()-4);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));
    painter.setPen(color);
    painter.drawPath(path);


}

//待优化  只需要初始化一次
void MainWindow::noteInit()
{

    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);
    //分组信息
    QList<QString>groups=controller.getGroups();
    ui->tab_note_combox_group->clear();
    //组装分组信息
    ui->tab_note_combox_group->addItem("所有分组");
    ui->tab_note_combox_group->addItem("未分组");
    ui->tab_note_combox_group->addItems(QStringList(groups));

    //单词列表初始化

    updateNoteList(getNoteList(ui->tab_note_list_button_sort->currentIndex()));
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
    QList<QString>list=controller.getGroups();
    for(int i=0;i<list.size();i++){
        QAction*action_move=new QAction(list.at(i),this);
        menuMove->addAction(action_move);
        connect(action_move, SIGNAL(triggered()),this,SLOT(tab_note_list_move()));
    }


    connect(ui->tab_note_list_listwidget,&QWidget::customContextMenuRequested,[=](const QPoint &pos)
       {
           menu->exec(QCursor::pos());
       });

    // 为动作设置信号槽

    connect(action_dele, SIGNAL(triggered()),this,SLOT(tab_note_list_delete()));

    connect(action_edit,SIGNAL(triggered()),this,SLOT(tab_note_list_edit()));

    connect(action_noreview,SIGNAL(triggered()),this,SLOT(tab_note_list_noreview()));

}

void MainWindow::tabBarInit(int index)
{

    ui->button_dict->setIcon(QIcon(":/images/dict.png"));
    ui->button_tran->setIcon(QIcon(":/images/trans.png"));
    ui->button_note->setIcon(QIcon(":/images/wb.png"));
    ui->button_doc->setIcon(QIcon(":/images/doc.png"));
    ui->button_interpret->setIcon(QIcon(":/images/tc.png"));
    ui->button_person->setIcon(QIcon(":/images/manual-trans.png"));
    ui->button_class->setIcon(QIcon(":/images/course.png"));

    ui->button_dict->setChecked(false);
    ui->button_tran->setChecked(false);
    ui->button_note->setChecked(false);
    ui->button_doc->setChecked(false);
    ui->button_interpret->setChecked(false);
    ui->button_person->setChecked(false);
    ui->button_class->setChecked(false);

    switch (index) {
    case 0:
        ui->button_dict->setIcon(QIcon(":/images/dict-hover.png"));
        ui->button_dict->setChecked(true);
        break;
    case 1:
        ui->button_tran->setIcon(QIcon(":/images/trans-hover.png"));
        ui->button_tran->setChecked(true);
        break;
    case 2:
        ui->button_note->setIcon(QIcon(":/images/wb-hover.png"));
        ui->button_note->setChecked(true);
        break;
    case 3:
        ui->button_doc->setIcon(QIcon(":/images/doc-hover.png"));
        ui->button_doc->setChecked(true);
        break;
    case 4:
        ui->button_interpret->setIcon(QIcon(":/images/tc-hover.png"));
        ui->button_interpret->setChecked(true);
        break;
    case 5:
        ui->button_person->setIcon(QIcon(":/images/manual-trans-hover.png"));
        ui->button_person->setChecked(true);
        break;
    case 6:
        ui->button_class->setIcon(QIcon(":/images/course-hover.png"));
        ui->button_class->setChecked(true);
        break;
    default:
        break;
    }
    ui->stackedWidget->setCurrentIndex(index);
}

void MainWindow::noteTabinit(int index)
{
    ui->tab_note_button_list->setChecked(false);
    ui->tab_note_button_card->setChecked(false);
    ui->tab_note_button_review->setChecked(false);

    switch(index){
    case 0:
        ui->tab_note_button_list->setChecked(true);
        break;
    case 1:
        ui->tab_note_button_card->setChecked(true);
        break;
    case 2:
        ui->tab_note_button_review->setChecked(true);
        break;

    }
}

void MainWindow::tabwidgetInit(int index)
{
    ui->stackwidget_title->show();

    ui->stackwidget_title->setCurrentIndex(index);

}

void MainWindow::initKey()
{
    //别忘了头文件<QShortcut>
    QShortcut *temp = new QShortcut(this);
    //设置键值，也就是设置快捷键.
    temp->setKey(tr("ctrl+alt+e"));
    //这个成员函数挺关键的，设置是否会自动反复按键.也就是说，当你一直按住键盘ctrl+r时，会一直不停的调用对应的槽函数.
    temp->setAutoRepeat(false);

    //连接信号与槽，showSlot()是自定义的槽函数!
    connect(temp, SIGNAL(activated()), this, SLOT(hideOrshow()));

}

void MainWindow::updateDict(dictBean bean)
{

    ui->dict_label_keyword->setText(bean.getKeyword());
    ui->dict_label_title->setText(bean.getTitle());
    ui->dict_edit_find->setText(bean.getKeyword());

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
                labelTitle->setText(QString::number(j+1)+"."+s);
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

    clearLayout(ui->scrollArea_simp->widget()->layout());
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
        labelTitle->setWordWrap(true);
        labelTitle->adjustSize();
        labelContent->setWordWrap(true);
        labelContent->adjustSize();
        if(iteratorTitle!=map.end()){
            labelTitle->setText(QString::number(i+1)+"."+iteratorTitle.value());
            layout_web->addWidget(labelTitle);
        }

        if(iteratorContent!=map.end()){
            labelContent->setText(iteratorContent.value());

            layout_web->addWidget(labelContent);
        }

    }
    layout_web->addStretch();
    clearLayout(ui->scrollArea_web->widget()->layout());
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
        labelTitle->setWordWrap(true);
        labelTitle->adjustSize();
        labelContent->setWordWrap(true);
        labelContent->adjustSize();
        if(iteratorTitle!=map.end()){
            labelTitle->setText(QString::number(i+1)+"."+iteratorTitle.value());

            layout_phrase->addWidget(labelTitle);
        }

        if(iteratorContent!=map.end()){
            labelContent->setText(iteratorContent.value());
            layout_phrase->addWidget(labelContent);
        }

    }
    layout_phrase->addStretch();
    clearLayout(ui->scrollArea_phrase->widget()->layout());
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
        labelTitle->setWordWrap(true);
        labelTitle->adjustSize();
        labelContent->setWordWrap(true);
        labelContent->adjustSize();
        if(iteratorTitle!=map.end()){
            labelTitle->setText(QString::number(i+1)+"."+iteratorTitle.value());
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
    clearLayout(ui->scrollArea_example->widget()->layout());
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

void MainWindow::installEventFilter()
{
    ui->button_dict->installEventFilter(this);
    ui->button_class->installEventFilter(this);
    ui->button_doc->installEventFilter(this);
    ui->button_interpret->installEventFilter(this);
    ui->button_note->installEventFilter(this);
    ui->button_person->installEventFilter(this);
    ui->button_tran->installEventFilter(this);
    ui->dict_doc->installEventFilter(this);
    ui->dict_shot->installEventFilter(this);
    ui->tab_note_list_button_setting->installEventFilter(this);
    ui->button_min->installEventFilter(this);
    ui->button_max->installEventFilter(this);
    ui->button_restore->installEventFilter(this);
    ui->tab_dict_from->installEventFilter(this);
    ui->tab_dict_to->installEventFilter(this);
}

void MainWindow::initQss()
{
    QFile file(":/qss/qss/dict.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    this->setStyleSheet(styleSheet);

    file.close();
}

void MainWindow::popSettingMenu()
{

    setting_menu->exec(ui->button_setting->mapToGlobal(ui->button_setting->mapFromParent(QPoint(ui->button_setting->pos().x(),
                                                                                                ui->button_setting->pos().y()+20))));
}

void MainWindow::initSettingMenu()
{
    if(settingwindow==NULL){

        setting_menu=new QMenu(this);
        setting_menu->setStyleSheet("QMenu::item{background-color:#fff;width:120px;height:40px;padding-left:50px;}"
                                                        "QMenu::item:selected {background-color: rgb(242, 150,150);color:#f00;}");
        QAction*action_vip=new QAction("开通VIP",this);
        action_vip->setData(QVariant(1));
        QAction*action_person=new QAction("个人信息",this);
        action_person->setData(QVariant(0));
        QAction*action_setting=new QAction("设置",this);
        action_setting->setData(QVariant(2));
        QAction*action_feedback=new QAction("意见反馈",this);
        action_feedback->setData(QVariant(4));
        QAction*action_manyi=new QAction("满意度调查",this);
        action_manyi->setData(QVariant(3));
        QAction*action_exit=new QAction("注销登录",this);
        action_exit->setData(QVariant(5));
        settingwindow=new settingWindow;

        connect(this,SIGNAL(settingChange(int)),settingwindow,SLOT(selectedTar(int)));
        connect(action_vip,SIGNAL(triggered()),settingwindow,SLOT(selectedTar()));
        connect(action_person,SIGNAL(triggered()),settingwindow,SLOT(selectedTar()));
        connect(action_setting,SIGNAL(triggered()),settingwindow,SLOT(selectedTar()));
        connect(action_feedback,SIGNAL(triggered()),settingwindow,SLOT(selectedTar()));
        connect(action_manyi,SIGNAL(triggered()),settingwindow,SLOT(selectedTar()));
        connect(action_exit,SIGNAL(triggered()),settingwindow,SLOT(selectedTar()));

        setting_menu->addAction(action_vip);
        setting_menu->addAction(action_person);

        setting_menu->addAction(action_setting);
        setting_menu->addAction(action_feedback);
        setting_menu->addAction(action_manyi);

        setting_menu->addAction(action_exit);
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *e)
{



    if (watched == ui->button_dict) {
            if (e->type() == QEvent::Enter)
                ui->button_dict->setIcon(QIcon(":/images/dict-hover.png"));
            else if(e->type()==QEvent::Leave&&!ui->button_dict->isChecked())
                ui->button_dict->setIcon(QIcon(":/images/dict.png"));

    }else if(watched==ui->button_tran){
        if(e->type()==QEvent::Enter)
            ui->button_tran->setIcon(QIcon(":/images/trans-hover.png"));
        else if(e->type()==QEvent::Leave&&!ui->button_tran->isChecked())
            ui->button_tran->setIcon(QIcon(":/images/trans.png"));

    }else if(watched==ui->button_note){
        if(e->type()==QEvent::Enter)
            ui->button_note->setIcon(QIcon(":/images/wb-hover.png"));
        else if(e->type()==QEvent::Leave&&!ui->button_note->isChecked())
            ui->button_note->setIcon(QIcon(":/images/wb.png"));
    }else if(watched==ui->button_doc){
        if(e->type()==QEvent::Enter)
            ui->button_doc->setIcon(QIcon(":/images/doc-hover.png"));
        else if(e->type()==QEvent::Leave&&!ui->button_doc->isChecked())
            ui->button_doc->setIcon(QIcon(":/images/doc.png"));
    }else if(watched==ui->button_interpret){
        if(e->type()==QEvent::Enter)
            ui->button_interpret->setIcon(QIcon(":/images/tc-hover.png"));
        else if(e->type()==QEvent::Leave&&!ui->button_interpret->isChecked())
            ui->button_interpret->setIcon(QIcon(":/images/tc.png"));

    }else if(watched==ui->button_person){
        if(e->type()==QEvent::Enter)
            ui->button_person->setIcon(QIcon(":/images/manual-trans-hover.png"));
        else if(e->type()==QEvent::Leave&&!ui->button_person->isChecked())
            ui->button_person->setIcon(QIcon(":/images/manual-trans.png"));

    }else if(watched==ui->button_class){
        if(e->type()==QEvent::Enter)
            ui->button_class->setIcon(QIcon(":/images/course-hover.png"));
        else if(e->type()==QEvent::Leave&&!ui->button_class->isChecked())
            ui->button_class->setIcon(QIcon(":/images/course.png"));
    }else if(watched==ui->dict_doc){
        if(e->type()==QEvent::Enter)
            ui->dict_doc->setIcon(QIcon(":/images/doc-trans-hover.png"));
        else if(e->type()==QEvent::Leave)
            ui->dict_doc->setIcon(QIcon(":/images/doc-trans.png"));
    }else if(watched==ui->dict_shot){
        if(e->type()==QEvent::Enter)
            ui->dict_shot->setIcon(QIcon(":/images/shot-trans-hover.png"));
        else if(e->type()==QEvent::Leave)
            ui->dict_shot->setIcon(QIcon(":/images/shot-trans.png"));

    }else if(watched==ui->tab_note_list_button_setting){
        if(e->type()==QEvent::Enter)
            ui->tab_note_list_button_setting->setIcon(QIcon(":/images/wb-setting-hover.png"));
        else if(e->type()==QEvent::Leave)
            ui->tab_note_list_button_setting->setIcon(QIcon(":/images/wb-setting-normal.png"));

    }else if(watched==ui->button_min){
        if(e->type()==QEvent::Enter)
            ui->button_min->setIcon(QIcon(":/images/minimum-hover.png"));
        else if(e->type()==QEvent::Leave)
            ui->button_min->setIcon(QIcon(":/images/minimum.png"));

    }else if(watched==ui->button_max){
        if(e->type()==QEvent::Enter)
            ui->button_max->setIcon(QIcon(":/images/maximum-hover.png"));
        else if(e->type()==QEvent::Leave)
            ui->button_max->setIcon(QIcon(":/images/maximum.png"));
    }else if(watched==ui->button_restore){
        if(e->type()==QEvent::Enter)
            ui->button_restore->setIcon(QIcon(":/images/restore-hover.png"));
        else if(e->type()==QEvent::Leave)
            ui->button_restore->setIcon(QIcon(":/images/restore.png"));
    }else if(watched==ui->tab_dict_from){
        if(e->type()==QEvent::Enter)
            ui->tab_dict_from->setIcon(QIcon(":/images/lang-drop-hover.png"));
        else if(e->type()==QEvent::Leave)
            ui->tab_dict_from->setIcon(QIcon(":/images/lang-drop.png"));
    }else if(watched==ui->tab_dict_to){
        if(e->type()==QEvent::Enter)
            ui->tab_dict_to->setIcon(QIcon(":/images/lang-drop-hover.png"));
        else if(e->type()==QEvent::Leave)
            ui->tab_dict_to->setIcon(QIcon(":/images/lang-drop.png"));
    }

        return QWidget::eventFilter(watched, e);
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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    is_press=true;
    startP=event->globalPos();
    windowP=this->frameGeometry().topLeft();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(is_press&&Qt::LeftButton)
        this->move(windowP+event->globalPos()-startP);


}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        is_press=false;
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type()!=QEvent::WindowStateChange)
        return;

    ui->button_max->setIcon(QIcon(":/images/maximum.png"));
    ui->button_restore->setIcon(QIcon(":/images/restore.png"));
    if(windowState()==Qt::WindowMaximized)
        //点击最大化
        ui->stackedWidget_maxmin->setCurrentIndex(1);
   else
        ui->stackedWidget_maxmin->setCurrentIndex(0);

}

QString MainWindow::packUrlDict(QString k)
{
    s->update();
    QString source=s->getSource();
    QString from=s->getFrom();
    QString to=s->getTo();
    QString url=QString("http://localhost:8080/dict?from=%1&to=%2&source=%3&key=%4")
            .arg(from).arg(to).arg(source).arg(k);

    return url;

}

QString MainWindow::packUrlTran(QString k)
{
    s->update();
    QString source=s->getSource();
    QString from=s->getFrom();
    QString to=s->getTo();
    QString url=QString("http://localhost:8080/tran?from=%1&to=%2&source=%3&key=%4")
            .arg(from).arg(to).arg(source).arg(k);

    return url;
}

QList<newWordBean> MainWindow::getNoteList(int index,QString keyword)
{
    QSqlDatabase database=ConnectPool::openConnection();
    QString group=ui->tab_note_combox_group->currentText();

    databaseController controller=databaseController::getInstance(database);
    QString param=NULL;
    if(!group.compare("未分组"))
        param="";
    else if(!group.compare("所有分组"))
        param=nullptr;
    else
        param=group;

    switch (index) {
    case 0:
        list_newWord=controller.getListOrderDatedesc(param,keyword);
        break;
    case 1:
        list_newWord=controller.getListOrderDateasc(param,keyword);
        break;
    case 2:
        list_newWord=controller.getListOrderWordAZ(param,keyword);
        break;
    case 3:
        list_newWord=controller.getListOrderWordZA(param,keyword);
        break;
    case 4:
        list_newWord=controller.getListOrderReviewFS(param,keyword);
        break;
    case 5:
        list_newWord=controller.getListOrderReviewSF(param,keyword);
        break;
    case 6:
        list_newWord=controller.getListOrderRandom(param,keyword);
        break;
    default:
        break;
    }
    ConnectPool::closeConnection(database);

    return list_newWord;

}

void MainWindow::updateNoteList(QList<newWordBean>list)
{
    ui->tab_note_list_listwidget->clear();

    if(list.size()==0){
        ui->dict_stackedWidget->setCurrentIndex(3);
        return;
    }
    ui->dict_stackedWidget->setCurrentIndex(0);
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


}

void MainWindow::updateNoteCard(int index)
{
    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);

    QList<newWordBean>list=getNoteList();
    int size=list.size();
    if(size==0){
        ui->dict_stackedWidget->setCurrentIndex(3);
        return;

    }
    ui->dict_stackedWidget->setCurrentIndex(1);
    if(index<0||index>=size)
        index=0;
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

void MainWindow::updateNoteReview(int index)
{
    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);

    //获取应该被复习的单词
    QList<newWordBean>list=getNoteList();
    int size=list.size();
    if(size==0){
        ui->dict_stackedWidget->setCurrentIndex(4);
        return;
    }
    ui->dict_stackedWidget->setCurrentIndex(2);
    if(index<0||index>=size)
        index=0;
    newWordBean bean=list.at(index);
    ui->tab_note_review_count->setText(QString::number(index+1)+"/"+QString::number(size));
    ui->tab_note_review_title->setText(bean.getName());
    ui->tab_note_review_expalin->setText(bean.getExplain());
    ui->tab_note_review_remember->show();
    ui->tab_note_review_noremember->show();
    ui->tab_note_review_button->show();
    ui->tab_note_review_expalin->hide();

}

void MainWindow::createSystemTray()
{
    //需判断托盘是否可用
    if(systemTrayIcon==NULL){
        QMenu*menu=new QMenu;
        menu->setStyleSheet("QMenu::item{width:120px;height:40px;padding-left:50px;}"
                            "QMenu::item:selected {background-color: rgb(242, 150,150);color:#f00;}");
        systemTrayIcon=new QSystemTrayIcon(QIcon(":/images/logo-shink.png"));

        QAction*action_screen=createWidgetAction(menu,"屏幕取词");
        QAction*action_delimit=createWidgetAction(menu,"划词翻译");
        QAction*action_shot=new QAction("截屏翻译");
        QAction*action_show=new QAction("显示主窗口");
        QAction*action_first=createWidgetAction(menu,"总在最前");
        QAction*action_feedback=new QAction("意见反馈");
        QAction*action_setting=new QAction("设置");
        QAction*action_exit=new QAction("退出");

        connect(action_shot,SIGNAL(triggered(bool)),this,SLOT(systemtray_shot()));
        connect(action_show,SIGNAL(triggered(bool)),this,SLOT(systemtray_show()));
        connect(action_feedback,SIGNAL(triggered(bool)),this,SLOT(systemtray_feedback()));
        connect(action_setting,SIGNAL(triggered(bool)),this,SLOT(systemtray_setting()));
        connect(action_exit,SIGNAL(triggered(bool)),this,SLOT(systemtray_exit()));


        menu->addAction(action_screen);
        menu->addAction(action_delimit);
        menu->addAction(action_show);
        menu->addAction(action_first);
        menu->addAction(action_feedback);
        menu->addAction(action_setting);
        menu->addAction(action_exit);
        systemTrayIcon->setContextMenu(menu);
    }

    systemTrayIcon->show();

}

QWidgetAction* MainWindow::createWidgetAction(QWidget*parent,QString s)
{
    QWidgetAction*action_shot=new QWidgetAction(parent);
    QCheckBox *checkbox=new QCheckBox;
    checkbox->setText(s);
    checkbox->setStyleSheet("QCheckBox::indicator::unchecked {padding-left:5px;image: url(:/images/switch-off.png);width:35px;height:35px;}"
                        "QCheckBox::indicator::checked {padding-left:5px;image: url(:/images/switch-on.png);width:35px;height:35px;color:#f00;}"
                            "QCheckBox{width:120px;height:40px;spacing:10px;color:#000;}"
                            "QCheckBox::hover{background-color:rgb(242, 150, 150);width:120px;height:40px;color:#f00;}");
    action_shot->setDefaultWidget(checkbox);
    connect(checkbox,SIGNAL(clicked()),this,SLOT(systemtray_checkbox()));

    return action_shot;
}

void MainWindow::clearLayout(QLayout *layout)
{

    if(layout==0)
        return;
    int itemCount=layout->count();

    for(int i=itemCount-1;i>=0;i--){
        QLayoutItem*item=layout->takeAt(i);
            if(item!=0) {
                 layout->removeWidget(item->widget());
                 delete item->widget();
            }


    }
    delete layout;
}

void MainWindow::systemtray_shot()
{

}

void MainWindow::systemtray_show()
{

    showNormal();
    raise();
    activateWindow();
}

void MainWindow::systemtray_feedback()
{
    emit settingChange(4);
}

void MainWindow::systemtray_setting()
{
    emit settingChange(2);
}

void MainWindow::systemtray_exit()
{
    close();
}

void MainWindow::systemtray_checkbox()
{


    QCheckBox*checkBox=(QCheckBox*)sender();

    if(!checkBox->text().compare("屏幕取词"))
        ui->checkBox_takeword->setChecked(checkBox->isChecked());
    else if(!checkBox->text().compare("划词翻译"))
        ui->checkBox_underline->setChecked(checkBox->isChecked());
    else{
        if(checkBox->isChecked())
            setWindowFlags(windowFlags()|Qt::WindowStaysOnTopHint);
        else
            setWindowFlags(windowFlags()&~Qt::WindowStaysOnTopHint);
        show();
    }


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
    updateNoteList(getNoteList(ui->tab_note_list_button_sort->currentIndex()));
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
    int result=QMessageBox::question(this,"提示","确定移动选中的单词到新的分组吗?","确定","取消");
    if(result)
        return;
    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);
    QAction* action=(QAction*)sender();
    QLabel* label=(QLabel*)(ui->tab_note_list_listwidget->itemWidget(
                ui->tab_note_list_listwidget->selectedItems()[0])->children().at(2));
    QString group=QString(action->text());
    QString name=QString(label->text());

    controller.changeGroupNameByName(group,name);


    updateNoteList(getNoteList(ui->tab_note_list_button_sort->currentIndex()));
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
    dict_note_add_window* window=new dict_note_add_window(this);
    window->show();


}

void MainWindow::tab_note_list_setting_setting()
{
    dict_preference_window* window=new dict_preference_window(this);
    window->show();
}

void MainWindow::hideOrshow()
{
    this->hide();
    QSystemTrayIcon* systemIcon=new QSystemTrayIcon(this);
    QIcon icon=QIcon("C:/Users/hzh17/Desktop/logo-shink.png");
    systemIcon->setIcon(icon);
    systemIcon->setToolTip("test测试");
    connect(systemIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(systemIconEvent(QSystemTrayIcon::ActivationReason)));
    systemIcon->show();


    QMenu* menu=new QMenu(this);
    QAction*action_show=new QAction("显示主页面");
    QAction*action_exit=new QAction("退出");
    menu->addAction(action_exit);
    menu->addAction(action_show);
    systemIcon->setContextMenu(menu);
}

void MainWindow::systemIconEvent(QSystemTrayIcon::ActivationReason reason)
{



    switch (reason) {
    case QSystemTrayIcon::Trigger:

        show();
        break;
    case QSystemTrayIcon::DoubleClick:

        break;
    case QSystemTrayIcon::Context:

        break;
    default:
        break;
    }
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
    player->setVolume(100);
    player->play();

    
}

void MainWindow::dictFind(QNetworkReply *reply)
{
    //进行网络操作,查询到数据
    QByteArray data=reply->readAll();
    QString s=data;
    if(s.isEmpty())
        return;
    dictbean=dictBean::fromJson(s);
    updateDict(dictbean);

    ui->tabWidget_dict->setCurrentIndex(1);
}

void MainWindow::tranFind(QNetworkReply *reply)
{
    QByteArray data=reply->readAll();
    QString s=data;

    tranbean=tranBean::fromJson(s);

    updateTran(tranbean);

}

void MainWindow::updateList()
{
    int index=ui->dict_stackedWidget->currentIndex();
    if(index==0)
        updateNoteList(getNoteList(ui->tab_note_list_button_sort->currentIndex()));
    else if(index==1){
        int i=ui->tab_note_card_count->text().left(ui->tab_note_card_count->text().indexOf('/')).toInt()-1;
        updateNoteCard(i);
    }
    else if(index==2)
        updateNoteReview(ui->tab_note_review_count->text().left(ui->tab_note_review_count->text().indexOf('/')).toInt()-1);
}



void MainWindow::on_dict_button_back_clicked()
{
    ui->tabWidget_dict->setCurrentIndex(0);
}


//点击单词查询按钮
void MainWindow::on_dict_find_clicked()
{
    if(ui->dict_edit->toPlainText().isEmpty())
        return;

    NetworkController *networkController=new NetworkController;

    if(!ui->dict_edit->toPlainText().compare(""))
        return;
    QNetworkAccessManager*manger=networkController->getUrl(packUrlDict(ui->dict_edit->toPlainText()).toUtf8().data());

    connect(manger,SIGNAL(finished(QNetworkReply*)), this, SLOT(dictFind(QNetworkReply*)));


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

    connect(manger,SIGNAL(finished(QNetworkReply*)), this, SLOT(playAudio(QNetworkReply*)));

}

//dict界面tab2
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
    ui->tran_edit_to->setText("");
}

void MainWindow::on_tran_button_tran_clicked()
{
    //进行翻译
    QString value=ui->tran_edit_from->toPlainText();


    NetworkController* controller=new NetworkController;
    QNetworkAccessManager*manger=controller->getUrl(packUrlTran(value).toUtf8().data());

    connect(manger,SIGNAL(finished(QNetworkReply*)), this, SLOT(tranFind(QNetworkReply*)));


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
    bean.setName(ui->dict_label_title->text());
    bean.setGroupName("");
    bean.setSoundMark("");
    bean.setExplain(explain);
    bean.setDateAdd(QDate::currentDate().toString("yyyy-MM-dd"));


    controller.insertNewWord(bean);


    ConnectPool::closeConnection(database);
}



void MainWindow::on_tab_note_button_list_clicked()
{
    ui->dict_stackedWidget->setCurrentIndex(0);
    showNoteTabbar(0);
    noteTabinit(0);
    updateNoteList(getNoteList());
}

//点击单词本->卡片
void MainWindow::on_tab_note_button_card_clicked()
{
    ui->dict_stackedWidget->setCurrentIndex(1);
    showNoteTabbar(1);
    noteTabinit(1);
    //进行数据的获取
    updateNoteCard(0);


}

void MainWindow::on_tab_note_button_review_clicked()
{
    ui->dict_stackedWidget->setCurrentIndex(2);
    showNoteTabbar(2);
    noteTabinit(2);
    updateNoteReview(0);
}



void MainWindow::on_tab_note_card_pre_clicked()
{
    int index=ui->tab_note_card_count->text().left(ui->tab_note_card_count->text().indexOf('/')).toInt()-1;

    //判断未实现

    updateNoteCard(index-1);
}

void MainWindow::on_tab_note_card_button_clicked()
{
    ui->tab_note_card_button->hide();

    ui->tab_note_card_expalin->show();
}

void MainWindow::on_tab_note_card_next_clicked()
{
    int index=ui->tab_note_card_count->text().left(ui->tab_note_card_count->text().indexOf('/')).toInt()-1;


    //判断未实现
    updateNoteCard(index+1);
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

void MainWindow::on_tab_note_review_button_clicked()
{
    ui->tab_note_review_button->hide();

    ui->tab_note_review_expalin->show();
}

void MainWindow::on_dict_edit_textChanged()
{
    /*if(ui->dict_edit->toPlainText().isEmpty())
        return;
    ui->tabWidget_dict->setCurrentIndex(1);
    NetworkController *networkController=new NetworkController;
    QString url=packUrlDict(ui->dict_edit->toPlainText());
    QNetworkAccessManager*manger=networkController->getUrl(url.toUtf8().data());

    connect(manger,SIGNAL(finished(QNetworkReply*)), this, SLOT(dictFind(QNetworkReply*)));*/
}

void MainWindow::on_dict_edit_find_textChanged(const QString &arg)
{
    if(!arg.compare(""))
        ui->tabWidget_dict->setCurrentIndex(0);
}

void MainWindow::on_tab_note_card_button_setting_clicked()
{
    dict_preference_window*window=new dict_preference_window;
    window->show();
}

void MainWindow::on_tab_note_review_button_setting_clicked()
{
    dict_preference_window*window=new dict_preference_window;
    window->show();
}



void MainWindow::on_tab_note_list_button_sort_currentIndexChanged(int index)
{
    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);

    updateNoteList(getNoteList(ui->tab_note_list_button_sort->currentIndex(),ui->tab_note_list_edit_find->text()));
    ConnectPool::closeConnection(database);
}

void MainWindow::on_tab_note_combox_group_currentIndexChanged(const QString &arg1)
{
    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);
    int index=ui->dict_stackedWidget->currentIndex();
    if(index==0)
        updateNoteList(getNoteList(ui->tab_note_list_button_sort->currentIndex(),ui->tab_note_list_edit_find->text()));
    else if(index==1)
        updateNoteCard();
    ConnectPool::closeConnection(database);

}

void MainWindow::on_tab_note_card_more_clicked()
{
    int index=ui->tab_note_card_count->text().left(ui->tab_note_card_count->text().indexOf('/')).toInt()-1;
    newWordBean obj=list_newWord.at(index);
    ui->tabWidget_dict->setCurrentIndex(1);
    NetworkController *networkController=new NetworkController;
    QString url=packUrlDict(obj.getName());
    QNetworkAccessManager*manger=networkController->getUrl(url.toUtf8().data());

    connect(manger,SIGNAL(finished(QNetworkReply*)), this, SLOT(dictFind(QNetworkReply*)));
}

void MainWindow::on_tab_note_card_edit_clicked()
{
    int index=ui->tab_note_card_count->text().left(ui->tab_note_card_count->text().indexOf('/')).toInt()-1;
    newWordBean obj=list_newWord.at(index);
    dict_edit* bean=new dict_edit(this,obj.getName());

    bean->show();
}

void MainWindow::on_tab_note_review_more_clicked()
{
    int index=ui->tab_note_card_count->text().left(ui->tab_note_card_count->text().indexOf('/')).toInt()-1;
    newWordBean obj=list_newWord.at(index);
    ui->tabWidget_dict->setCurrentIndex(1);
    NetworkController *networkController=new NetworkController;
    QString url=packUrlDict(obj.getName());
    QNetworkAccessManager*manger=networkController->getUrl(url.toUtf8().data());

    connect(manger,SIGNAL(finished(QNetworkReply*)), this, SLOT(dictFind(QNetworkReply*)));
}


void MainWindow::on_tab_note_list_edit_find_textChanged(const QString &value)
{

    updateNoteList(getNoteList(ui->tab_note_list_button_sort->currentIndex(),value));
}

void MainWindow::on_tab_note_combox_group_currentIndexChanged(int index)
{

}

void MainWindow::on_button_dict_clicked()
{
    tabBarInit(0);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackwidget_title->hide();
}

void MainWindow::on_button_tran_clicked()
{
    tabBarInit(1);
    tabwidgetInit(0);

}

void MainWindow::on_button_note_clicked()
{
    tabBarInit(2);
    noteInit();
    tabwidgetInit(1);

    ui->dict_stackedWidget->setCurrentIndex(0);
    showNoteTabbar(0);
    noteTabinit(0);
    updateNoteList(getNoteList());
}

void MainWindow::on_button_doc_clicked()
{
    tabBarInit(3);
    tabwidgetInit(2);
}

void MainWindow::on_button_interpret_clicked()
{
    tabBarInit(4);

}

void MainWindow::on_button_person_clicked()
{
    tabBarInit(5);
    tabwidgetInit(1);
}



void MainWindow::on_button_class_clicked()
{
    tabBarInit(6);
    tabwidgetInit(1);
}

void MainWindow::on_button_logo_clicked()
{

    tabBarInit(0);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackwidget_title->hide();
}

void MainWindow::on_button_close_clicked()
{
    close();
}

void MainWindow::on_button_max_clicked()
{
    showMaximized();
}

void MainWindow::on_button_min_clicked()
{
    showMinimized();

}

void MainWindow::on_button_restore_clicked()
{
    showNormal();
}

void MainWindow::on_button_setting_clicked()
{
    popSettingMenu();
}


void MainWindow::on_tab_note_review_remember_clicked()
{
    int index=ui->tab_note_review_count->text().left(ui->tab_note_card_count->text().indexOf('/')).toInt()-1;


    //判断未实现
    updateNoteReview(index+1);
}

void MainWindow::on_tab_note_review_noremember_clicked()
{
    int index=ui->tab_note_review_count->text().left(ui->tab_note_card_count->text().indexOf('/')).toInt()-1;


    //判断未实现
    updateNoteReview(index+1);
}

void MainWindow::on_pushButton_clicked()
{
    popSettingMenu();
}

void MainWindow::on_tab_dict_from_clicked()
{
    if(languagewindow_dict==NULL)
        languagewindow_dict=new languagewindow(this);
    QPoint p=mapToParent(ui->tab_dict_from->pos());

    languagewindow_dict->setGeometry(200+p.x(),p.y()+80,510,208);

    languagewindow_dict->show();
}

void MainWindow::on_dict_edit_find_textEdited(const QString &arg)
{
    if(!strcmp(arg.toUtf8().data(),"")){
        ui->tabWidget_dict->setCurrentIndex(0);
        ui->dict_edit->setText("");
    }else if(strcmp(arg.toUtf8().data(),"")){
        //执行查询操作
        NetworkController *networkController=new NetworkController;

        QNetworkAccessManager*manger=networkController->getUrl(packUrlDict(arg).toUtf8().data());

        connect(manger,SIGNAL(finished(QNetworkReply*)), this, SLOT(dictFind(QNetworkReply*)));


    }
}
