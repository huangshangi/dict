#include "dict_tran.h"
#include "ui_dict_tran.h"

dict_tran::dict_tran(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dict_tran)
{
    ui->setupUi(this);

}

dict_tran::~dict_tran()
{
    delete ui;
}
