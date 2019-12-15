#ifndef DICT_PREFERENCE_WINDOW_H
#define DICT_PREFERENCE_WINDOW_H

#include <QMainWindow>
#include "config.h"
#include "settings.h"
#include <QIntValidator>
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

private slots:
    void on_pushButton_sure_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::dict_preference_window *ui;
};

#endif // DICT_PREFERENCE_WINDOW_H
