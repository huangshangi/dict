#include "languagewindow.h"
#include "ui_languagewindow.h"

languagewindow::languagewindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::languagewindow)
{
    ui->setupUi(this);
}

languagewindow::~languagewindow()
{
    delete ui;
}
