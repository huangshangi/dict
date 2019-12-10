#include "groupmanagment.h"
#include "ui_groupmanagment.h"

groupmanagment::groupmanagment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::groupmanagment)
{
    ui->setupUi(this);

    updateListWidget();


}

groupmanagment::~groupmanagment()
{
    delete ui;
}

void groupmanagment::updateListWidget()
{
    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);
    ui->listWidget->clear();
    //查询到组别信息
    QList<QString>list=controller.getGroups();

    for(int i=0;i<list.size();i++){
        QListWidgetItem*item=new QListWidgetItem;
        QHBoxLayout*layout=new QHBoxLayout;
        QWidget*widget=new QWidget;

        QLineEdit*lineedit=new QLineEdit;
        QPushButton*button=new QPushButton;

        lineedit->setText(list.at(i));
        button->setText("删除");
        lineedit->setEnabled(false);

        layout->addWidget(lineedit,9,Qt::AlignLeft);
        layout->addWidget(button,1,Qt::AlignRight);

        widget->setLayout(layout);

        QSize size=item->sizeHint();

        item->setSizeHint(QSize(size.width(),50));
        ui->listWidget->addItem(item);
        widget->setSizeIncrement(size.width(),50);
        ui->listWidget->setItemWidget(item,widget);
        connect(lineedit,SIGNAL(returnPressed()),this,SLOT(lineeditClicked()));
        connect(button,SIGNAL(clicked()),this,SLOT(itemClicked()));
    }
    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(doubleClicked(QListWidgetItem*)));
    ConnectPool::closeConnection(database);
}

void groupmanagment::doubleClicked(QListWidgetItem *item)
{

    QWidget*widget=ui->listWidget->itemWidget(item);
    QLineEdit*lineedit=(QLineEdit*)widget->children().at(1);

    lineedit->setEnabled(true);
    lineedit->setFocus();
    lineedit->setSelection(0,lineedit->text().size());
    seleLine=lineedit->text();
}

void groupmanagment::lineeditClicked()
{

    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);

    QListWidgetItem*item=ui->listWidget->itemAt(ui->listWidget->mapFromGlobal(QCursor::pos()));

    QWidget*widget=ui->listWidget->itemWidget(item);
    QLineEdit*label=(QLineEdit*)widget->children().at(1);
    label->setEnabled(false);
    QString s=label->text();

    if(!s.isEmpty())
        controller.changeGroupName(seleLine,s);

    ConnectPool::closeConnection(database);
}

//实行删除操作
void groupmanagment::itemClicked()
{


    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);

    QListWidgetItem*item=ui->listWidget->itemAt(ui->listWidget->mapFromGlobal(QCursor::pos()));

    int result=QMessageBox::question(this,"提示","确定删除该分组吗?","确定","取消");

    if(result)
        return;
    QWidget*widget=ui->listWidget->itemWidget(item);
    QLineEdit*label=(QLineEdit*)widget->children().at(1);
    QString s=label->text();

    if(!s.isEmpty())
        if(controller.deleteGroup(s))
            ui->listWidget->removeItemWidget(item);
    ConnectPool::closeConnection(database);

}

void groupmanagment::on_lineEdit_returnPressed()
{
    ui->listWidget->setFocus();

    if(ui->lineEdit->text().isEmpty())
        return;

    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);
    QString s=ui->lineEdit->text();
    controller.addGroup(s);

    ConnectPool::closeConnection(database);
    updateListWidget();
    ui->lineEdit->clear();
}
