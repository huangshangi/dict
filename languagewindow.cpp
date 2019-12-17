#include "languagewindow.h"
#include "ui_languagewindow.h"

languagewindow::languagewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::languagewindow)
{
    ui->setupUi(this);
    ui->button_from->installEventFilter(this);
    ui->button_to->installEventFilter(this);
    initList();
    initUi();

    setWindowFlags(Qt::FramelessWindowHint);
    fromButton=new QPushButton;
    fromButton->setText("");

    toButton=new QPushButton;
    toButton->setText("");

}

languagewindow::~languagewindow()
{
    delete ui;
}

bool languagewindow::eventFilter(QObject *watched, QEvent *e)
{
    if (watched == ui->button_from) {
            if (e->type() == QEvent::Enter)
                ui->button_from->setIcon(QIcon(":/images/lang-drop-red.png"));
            else if(e->type()==QEvent::Leave&&!ui->button_from->isChecked())
                ui->button_from->setIcon(QIcon(":/images/lang-drop.png"));

    }else if (watched == ui->button_to) {
        if (e->type() == QEvent::Enter)
            ui->button_to->setIcon(QIcon(":/images/lang-drop-red.png"));
        else if(e->type()==QEvent::Leave&&!ui->button_to->isChecked())
            ui->button_to->setIcon(QIcon(":/images/lang-drop.png"));

}

    return QWidget::eventFilter(watched,e);
}

bool languagewindow::event(QEvent *event)
{
    if (event->type() == QEvent::ActivationChange)
        {
            if(QApplication::activeWindow() != this)
            {
                this->close();
            }
        }
        return QWidget::event(event);
}

void languagewindow::initList()
{
    QString s="自动检测语言,英汉互译,法汉互译,韩汉互译,日汉互译,日韩互译,德汉互译,俄汉互译,葡汉互译,西汉互译";
    QString ss="阿拉伯文,阿尔波尼亚文,阿姆哈拉文,阿塞拜疆文,爱尔兰文,爱沙尼亚文,巴斯克文,白俄罗斯文,保加利亚文,"
               "冰岛文,波兰文,波斯尼亚文(拉丁文),波斯文,丹麦文,德文,俄文,法文,菲律宾文,芬兰文,弗里斯兰文,"
               "高棉文,格鲁吉亚文,古吉拉特文,哈萨克文,海地文,韩文,豪萨文,荷兰文,吉尔吉斯坦文,加利西亚文,"
               "加泰罗尼亚文,捷克文,卡纳达文";



    list_common=s.split(",");
    list_assign=ss.split(",");

}

void languagewindow::initUi()
{

    for(int i=0;i<(list_common.size()-1)/5+1;i++){

        for(int j=0;j<5&&list_common.size()>i*5+j;j++){
            QPushButton*button=new QPushButton;
            button->setText(list_common.at(i*5+j));

            button->setStyleSheet("QPushButton{text-align:left;background-color:transparent;border:none;}"
                                  "QPushButton:hover{text-align:left;color:#f00;background-color:transparent;}");

            connect(button,SIGNAL(clicked()),this,SLOT(common_click()));
            ui->tableWidget_common->setCellWidget(i,j,button);

        }
    }

    ui->tableWidget_assign->setColumnCount(3);
    ui->tableWidget_assign->setRowCount((list_assign.size()-1)/5+1);
    for(int i=0;i<(list_assign.size()-1)/5+1;i++){

        for(int j=0;j<3&&list_assign.size()>i*3+j;j++){
            QPushButton*button=new QPushButton;
            button->setText(list_assign.at(i*3+j));
            button->setStyleSheet("QPushButton{text-align:left;background-color:transparent;border:none;}"
                                      "QPushButton:hover{text-align:left;color:#f00;background-color:transparent;}");
            connect(button,SIGNAL(clicked()),this,SLOT(assign_click()));
            ui->tableWidget_assign->setCellWidget(i,j,button);
        }
    }

}

void languagewindow::button_from_click()
{

    if(fromButton->text()!=""&&state==1)
        fromButton->setStyleSheet("QPushButton{text-align:left;background-color:transparent;border:none;}"
                             "QPushButton:hover{text-align:left;color:#f00;background-color:transparent;}");
    if(fromButton->text()!=""&&state==2)
        fromButton->setStyleSheet("QPushButton{text-align:left;background-color:transparent;border:none;color:red}");
    if(toButton->text()!="")
        toButton->setStyleSheet("QPushButton{color:#dfdfdf;text-align:left;background-color:transparent;border:none;}");



}

void languagewindow::button_to_click()
{

    if(toButton->text()!=""&&state==2)
        toButton->setStyleSheet("QPushButton{text-align:left;background-color:transparent;border:none;}"
                             "QPushButton:hover{text-align:left;color:#f00;background-color:transparent;}");

    if(toButton->text()!=""&&state==1)
        toButton->setStyleSheet("QPushButton{text-align:left;background-color:transparent;border:none;color:red}");
    if(fromButton->text()!="")
        fromButton->setStyleSheet("QPushButton{color:#dfdfdf;text-align:left;background-color:transparent;border:none;}");


}



void languagewindow::common_click()
{
    QPushButton *button=(QPushButton*)sender();

}

void languagewindow::assign_click()
{
    QPushButton *button=(QPushButton*)sender();
    if(button==fromButton||button==toButton)
        return;
    button->setStyleSheet("QPushButton{text-align:left;background-color:transparent;border:none;color:red}");
    button->setCheckable(false);

    //将原始被点击的按钮回复
    if(state==1){
        //当前处于from下拉框
        button_from_click();
        fromButton=button;
        ui->button_from->setText(button->text());
    }else if(state==2){
        button_to_click();
        toButton=button;
        ui->button_to->setText(button->text());
    }

}


void languagewindow::on_button_from_clicked()
{
    strechWindow();
    ui->button_to->setChecked(false);

    button_from_click();
    state=1;
}

int languagewindow::findInList(QString value, QStringList list)
{
    int index=0;
    for(QString temp:list){
        if(value==temp)
            break;
        index++;
    }

    return index;
}



void languagewindow::on_button_to_clicked()
{
    ui->button_from->setChecked(false);
    strechWindow();
    button_to_click();
    state=2;
}

void languagewindow::strechWindow()
{
    QRect rect=geometry();
    rect.setHeight(539);
    setGeometry(rect);
}
