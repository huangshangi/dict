#include "dict_preference_window.h"
#include "ui_dict_preference_window.h"

dict_preference_window::dict_preference_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dict_preference_window)
{
    ui->setupUi(this);
}

dict_preference_window::~dict_preference_window()
{
    delete ui;
}

void dict_preference_window::on_pushButton_sure_clicked()
{
    close();
}

void dict_preference_window::on_pushButton_cancel_clicked()
{
    close();
}
