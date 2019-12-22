#ifndef DICT_PREFERENCE_WINDOW_H
#define DICT_PREFERENCE_WINDOW_H

#include <QMainWindow>
#include "config.h"
#include "settings.h"
#include <QIntValidator>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
namespace Ui {
class dict_preference_window;
}

class dict_preference_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit dict_preference_window(QWidget *parent = 0);
    ~dict_preference_window();

    void paintEvent(QPaintEvent*event);

    void mousePressEvent(QMouseEvent *event);    //鼠标点击事件
    void mouseMoveEvent(QMouseEvent *event);     //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *event);  //鼠标释放事件

private slots:
    void on_pushButton_sure_clicked();

    void on_pushButton_cancel_clicked();

    void on_button_close_clicked();

private:
    Ui::dict_preference_window *ui;

    //以下变量用于窗口拖动
    bool is_press;
    QPoint startP;//鼠标点击坐标
    QPoint windowP;//窗口坐标
};

#endif // DICT_PREFERENCE_WINDOW_H
