#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>
#include "settings.h"
#include "config.h"
namespace Ui {
class settingWindow;
}

class settingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit settingWindow(QWidget *parent = 0);
    ~settingWindow();

private slots:


    void on_radioButton_big_clicked();

    void on_radioButton_normal_clicked();

    void on_tab_normal_startup_bootup_clicked();

    void on_tab_normal_startup_bootup_toggled(bool checked);

private:
    Ui::settingWindow *ui;

    Config config;

    settings* setting;
};

#endif // SETTINGWINDOW_H
