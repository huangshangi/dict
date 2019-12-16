#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "settings.h"
#include "config.h"
#include "customtabstyle.cpp"
namespace Ui {
class settingWindow;
}

class settingWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit settingWindow(QWidget *parent = 0);
    ~settingWindow();

    void closeEvent(QCloseEvent *event);

    void tarbarInit(int index);

public slots:
        void selectedTar();
private slots:


    void on_radioButton_big_clicked();

    void on_radioButton_normal_clicked();


    void on_tab_normal_startup_bootup_toggled(bool checked);

    void on_tab_normal_startup_min_toggled(bool checked);

    void on_tab_normal_mainwindow_first_toggled(bool checked);

    void on_tab_normal_mainwindow_min_toggled(bool checked);

    void on_tab_normal_rightClick_add_toggled(bool checked);

    void on_tab_content_audio_toggled(bool checked);

    void on_tab_content_history_count_valueChanged(int arg1);

    void on_button_person_clicked();

    void on_button_vip_clicked();

    void on_button_setting_clicked();

    void on_button_manyi_clicked();

    void on_button_feedback_clicked();

    void on_button_about_clicked();

private:
    Ui::settingWindow *ui;

    Config config;

    settings* setting;
};

#endif // SETTINGWINDOW_H
