#ifndef DICT_NOTE_ADD_WINDOW_H
#define DICT_NOTE_ADD_WINDOW_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QDate>
#include "connectpool.h"
#include "databasecontroller.h"
#include "newwordbean.h"
#include <QCloseEvent>
#include "mainwindow.h"
namespace Ui {
class dict_note_add_window;
}

class dict_note_add_window : public QMainWindow
{
    Q_OBJECT
signals:
    void updateList();
public:
    explicit dict_note_add_window(QWidget *parent = 0);
    ~dict_note_add_window();
    void closeEvent(QCloseEvent*closeEvent);


    void paintEvent(QPaintEvent*event);

    void mousePressEvent(QMouseEvent *event);    //鼠标点击事件
    void mouseMoveEvent(QMouseEvent *event);     //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);  //鼠标释放事件
private slots:
    void on_button_sure_clicked();

    void on_button_cancel_clicked();

    void on_button_close_clicked();

private:
    Ui::dict_note_add_window *ui;

    //以下变量用于窗口拖动
    bool is_press;
    QPoint startP;//鼠标点击坐标
    QPoint windowP;//窗口坐标
};

#endif // DICT_NOTE_ADD_WINDOW_H
