#include "settingwindow.h"
#include "ui_settingwindow.h"

settingWindow::settingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::settingWindow)
{
    ui->setupUi(this);
}

settingWindow::~settingWindow()
{
    delete ui;
}
