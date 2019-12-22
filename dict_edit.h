#ifndef DICT_EDIT_H
#define DICT_EDIT_H

#include <QMainWindow>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMouseEvent>
#include <QPainter>
#include "databasecontroller.h"
#include "connectpool.h"
#include "newwordbean.h"
#include <QCloseEvent>
namespace Ui {
class dict_edit;
}

class dict_edit : public QMainWindow
{
    Q_OBJECT
signals:
    void updateList();
public:
    explicit dict_edit(QWidget *parent = 0);
    dict_edit(QWidget *parent ,QString name);
    ~dict_edit();

    QString getName() const;
    void setName(const QString &value);

    void closeEvent(QCloseEvent*closeEvent);

    void paintEvent(QPaintEvent*event);

    void mousePressEvent(QMouseEvent *event);    //鼠标点击事件
    void mouseMoveEvent(QMouseEvent *event);     //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);  //鼠标释放事件

private slots:
    void on_dict_edit_button_dict_clicked();

    void on_dict_edit_button_sure_clicked();

    void on_dict_edit_button_cancel_clicked();

    void on_button_close_clicked();

private:
    Ui::dict_edit *ui;
    QString name;

    //以下变量用于窗口拖动
    bool is_press;
    QPoint startP;//鼠标点击坐标
    QPoint windowP;//窗口坐标
};

#endif // DICT_EDIT_H
