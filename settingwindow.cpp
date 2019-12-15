#include "settingwindow.h"
#include "ui_settingwindow.h"

settingWindow::settingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::settingWindow)
{
    ui->setupUi(this);


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




void settingWindow::on_radioButton_big_clicked()
{
    setting->setFont(false);
}

void settingWindow::on_radioButton_normal_clicked()
{
    setting->setFont(true);
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
