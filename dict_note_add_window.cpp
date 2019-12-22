#include "dict_note_add_window.h"
#include "ui_dict_note_add_window.h"

dict_note_add_window::dict_note_add_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dict_note_add_window)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint |Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);

    connect(this,SIGNAL(updateList()),parent,SLOT(updateList()));
}

dict_note_add_window::~dict_note_add_window()
{
    delete ui;
}

void dict_note_add_window::closeEvent(QCloseEvent *closeEvent)
{


    emit updateList();
}

void dict_note_add_window::paintEvent(QPaintEvent *event)
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

void dict_note_add_window::mousePressEvent(QMouseEvent *event)
{
    is_press=true;
    startP=event->globalPos();
    windowP=this->frameGeometry().topLeft();
}

void dict_note_add_window::mouseMoveEvent(QMouseEvent *event)
{
    if(is_press&&Qt::LeftButton)
        this->move(windowP+event->globalPos()-startP);
}

void dict_note_add_window::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        is_press=false;
}

void dict_note_add_window::on_button_sure_clicked()
{
    //将信息添加至单词本
    QString name=ui->edit_dict->text();
    QString mask=ui->edit_mask->text();
    QString group=ui->comboBox->currentText();
    QString explain=ui->edit_explain->toPlainText();

    if(name.isEmpty()||explain.isEmpty()){

        //弹出消息
     }
    QString date=QDate::currentDate().toString("yyyy-MM-dd");

    newWordBean bean(name,group,mask,explain,date);

    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);
    controller.insertNewWord(bean);
    ConnectPool::closeConnection(database);

    close();
}

void dict_note_add_window::on_button_cancel_clicked()
{
    close();
}



void dict_note_add_window::on_button_close_clicked()
{
    close();
}
