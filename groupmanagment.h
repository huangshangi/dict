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
#include <QPainter>
#include <QMouseEvent>
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

    //鼠标移动事件
    void mousePressEvent(QMouseEvent *event);    //鼠标点击事件
    void mouseMoveEvent(QMouseEvent *event);     //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);  //鼠标释放事件


    void paintEvent(QPaintEvent*event);
private:
    Ui::groupmanagment *ui;

    void updateListWidget();

    QString seleLine;

    //以下变量用于窗口拖动
    bool is_press;
    QPoint startP;//鼠标点击坐标
    QPoint windowP;//窗口坐标

private slots:
    void itemClicked();
    void on_lineEdit_returnPressed();
    void doubleClicked(QListWidgetItem*item);
    void lineeditClicked();
    void on_button_close_clicked();
};

#endif // GROUPMANAGMENT_H
