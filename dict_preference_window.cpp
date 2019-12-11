#include "dict_preference_window.h"
#include "ui_dict_preference_window.h"

dict_preference_window::dict_preference_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dict_preference_window)
{
    ui->setupUi(this);
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
