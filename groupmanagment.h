#ifndef GROUPMANAGMENT_H
#define GROUPMANAGMENT_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QListWidget>
#include <QLineEdit>
#include "databasecontroller.h"
#include "connectpool.h"
namespace Ui {
class groupmanagment;
}

class groupmanagment : public QMainWindow
{
    Q_OBJECT

public:
    explicit groupmanagment(QWidget *parent = 0);
    ~groupmanagment();

private:
    Ui::groupmanagment *ui;

    void updateListWidget();

    QString seleLine;

private slots:
    void itemClicked();
    void on_lineEdit_returnPressed();
    void doubleClicked(QListWidgetItem*item);
    void lineeditClicked();
};

#endif // GROUPMANAGMENT_H
