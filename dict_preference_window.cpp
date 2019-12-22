#include "dict_preference_window.h"
#include "ui_dict_preference_window.h"

dict_preference_window::dict_preference_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dict_preference_window)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint |Qt::WindowSystemMenuHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);

    QFile file(":/qss/qss/preference.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = tr(file.readAll());
    this->setStyleSheet(styleSheet);
    file.close();

    ui->lineEdit->setValidator(new QIntValidator(1,1000,this));


}

dict_preference_window::~dict_preference_window()
{
    delete ui;
}

void dict_preference_window::on_pushButton_sure_clicked()
{
    Config config;
    QString path="note";
    config.set(path,"review-remind",ui->checkBox_remind->isChecked());
    config.set(path,"review-audio",ui->checkBox_review->isChecked());
    config.set(path,"review-add",ui->checkBox_reviewadd->isChecked());
    config.set(path,"find-add",ui->checkBox_noteadd->isChecked());
    config.set(path,"play-show",ui->checkBox_showexplain->isChecked());
    config.set(path,"reivew-max",ui->lineEdit->text());
    config.set(path,"default-note",ui->comboBox->currentText());
    config.set("content","browse-audio",ui->checkBox_browse->isChecked());
    settings::update();
    close();
}

void dict_preference_window::on_pushButton_cancel_clicked()
{
    close();
}

void dict_preference_window::paintEvent(QPaintEvent *event)
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

void dict_preference_window::mousePressEvent(QMouseEvent *event)
{
    is_press=true;
    startP=event->globalPos();
    windowP=this->frameGeometry().topLeft();
}

void dict_preference_window::mouseMoveEvent(QMouseEvent *event)
{
    if(is_press&&Qt::LeftButton)
        this->move(windowP+event->globalPos()-startP);
}

void dict_preference_window::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        is_press=false;
}

void dict_preference_window::on_button_close_clicked()
{
    close();
}
