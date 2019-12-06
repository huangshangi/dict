#include "dict.h"
#include "ui_dict.h"

dict::dict(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dict)
{
    ui->setupUi(this);
    dictTran=new dict_tran;


}

dict::~dict()
{
    delete ui;
}

void dict::requestFinished(QNetworkReply*reply) {
    QString s = QString(QByteArray(reply->readAll()));

    ui->textEdit->setText(s);
}





void dict::on_dict_find_clicked()
{
    dictTran->show();
}
