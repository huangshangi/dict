#include "settingwindow.h"
#include "ui_settingwindow.h"

settingWindow::settingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::settingWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);


    //初始化设置界面
    setting=settings::getInstance();
    //设置字体
    if(setting->getFont())
        ((QRadioButton*)(ui->tab_setting_normal_groupBox_font->children().at(1)))->setChecked(true);
    else
        ((QRadioButton*)(ui->tab_setting_normal_groupBox_font->children().at(0)))->setChecked(true);

    ui->tab_normal_startup_bootup->setChecked(setting->getStartup_bootup());
    ui->tab_normal_startup_min->setChecked(setting->getStartup_min());
    ui->tab_normal_mainwindow_first->setChecked(setting->getMainwindow_first());
    ui->tab_normal_mainwindow_min->setChecked(setting->getMainwindow_min());
    ui->tab_normal_rightClick_add->setChecked(setting->getRightClick_add());
    ui->tab_content_audio->setChecked(setting->getBrowse_audio());
    ui->tab_content_history_count->setValue(setting->getHistory());

}

settingWindow::~settingWindow()
{
    delete ui;
}

void settingWindow::closeEvent(QCloseEvent *event)
{
    settings::writeTo(setting);
}

void settingWindow::paintEvent(QPaintEvent *event)
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

void settingWindow::tarbarInit(int index)
{
    ui->button_about->setChecked(false);
    ui->button_feedback->setChecked(false);
    ui->button_manyi->setChecked(false);
    ui->button_person->setChecked(false);
    ui->button_setting->setChecked(false);
    ui->button_vip->setChecked(false);

    switch(index){
    case 0:ui->button_person->setChecked(true);break;
    case 1:ui->button_vip->setChecked(true);break;
    case 2:ui->button_setting->setChecked(true);break;
    case 3:ui->button_manyi->setChecked(true);break;
    case 4:ui->button_feedback->setChecked(true);break;
    case 5:ui->button_about->setChecked(true);break;

    }

    ui->stackedWidget->setCurrentIndex(index);
}




void settingWindow::on_radioButton_big_clicked()
{
    setting->setFont(false);
}

void settingWindow::on_radioButton_normal_clicked()
{
    setting->setFont(true);
}

void settingWindow::selectedTar()
{

    //setParent((QWidget*)sender()->parent());
    int index=((QAction*)sender())->data().toInt();
    tarbarInit(index);
    show();
}

void settingWindow::selectedTar(int index)
{
    //setParent((QWidget*)sender()->parent());
    ui->stackedWidget->setCurrentIndex(index);
    tarbarInit(index);
    show();
}


void settingWindow::on_tab_normal_startup_bootup_toggled(bool checked)
{
    setting->setStartup_bootup(checked);
}

void settingWindow::on_tab_normal_startup_min_toggled(bool checked)
{
    setting->setStartup_min(checked);
}

void settingWindow::on_tab_normal_mainwindow_first_toggled(bool checked)
{
    setting->setMainwindow_first(checked);
}

void settingWindow::on_tab_normal_mainwindow_min_toggled(bool checked)
{
    setting->setMainwindow_min(checked);
}

void settingWindow::on_tab_normal_rightClick_add_toggled(bool checked)
{
    setting->setRightClick_add(checked);
}

void settingWindow::on_tab_content_audio_toggled(bool checked)
{
    setting->setBrowse_audio(checked);
}

void settingWindow::on_tab_content_history_count_valueChanged(int arg1)
{
    setting->setHistory(arg1);
}

void settingWindow::on_button_person_clicked()
{
    tarbarInit(0);
}

void settingWindow::on_button_vip_clicked()
{
    tarbarInit(1);
}

void settingWindow::on_button_setting_clicked()
{
    tarbarInit(2);
}

void settingWindow::on_button_manyi_clicked()
{
    tarbarInit(3);
}

void settingWindow::on_button_feedback_clicked()
{
    tarbarInit(4);
}

void settingWindow::on_button_about_clicked()
{
    tarbarInit(5);
}

void settingWindow::on_button_close_clicked()
{
    close();
}

void settingWindow::mousePressEvent(QMouseEvent *event)
{

    is_press=true;
    startP=event->globalPos();
    windowP=this->frameGeometry().topLeft();
}

void settingWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(is_press&&Qt::LeftButton)
        this->move(windowP+event->globalPos()-startP);


}

void settingWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
        is_press=false;
}
