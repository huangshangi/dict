#include "languagewindow.h"
#include "ui_languagewindow.h"

languagewindow::languagewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::languagewindow)
{
    ui->setupUi(this);

    for(int i=0;i<9;i++){

        QLabel*label=new QLabel;
        label->setText("ceshi");
        ui->gridLayout->addWidget(label,i/5,i%5+1);

    }
}

languagewindow::~languagewindow()
{
    delete ui;
}

void languagewindow::on_label_2_linkHovered(const QString &link)
{
    qDebug()<<link;
}

void languagewindow::on_label_2_linkActivated(const QString &link)
{
    qDebug()<<link;
}
