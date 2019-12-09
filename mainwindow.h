#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include <CustomTabStyle.cpp>
#include <QFileDialog>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QMessageBox>
#include "NetworkController.h"
#include "dict_tran.h"
#include "dict.h"
#include "capture.h"
#include "dictbean.h"
#include "tranbean.h"
#include "dict_simpbean.h"
#include "dict_webbean.h"
#include "dict_phrasebean.h"
#include "dict_examplebean.h"
#include "databasecontroller.h"
#include "ConnectPool.h"
#define TRAN_FROM_MAX_LENGTH 5000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateDict(dictBean bean);
    void updateTran(tranBean bean);

    void hideTranWidget();
    void showTranWidget();


private:
    Ui::MainWindow *ui;
    tranBean tranbean;
    dictBean dictbean;
public slots:


private slots:
    void test();
    void playAudio(QNetworkReply*reply);
    void on_dict_button_back_clicked();
    void on_dict_find_clicked();
    void on_dict_doc_clicked();
    void on_dict_shot_clicked();
    void on_dict_button_pron_clicked();
    void on_dict_button_find_clicked();
    void on_tran_edit_from_textChanged();
    void on_tran_button_clear_clicked();
    void on_tran_button_tran_clicked();
    void on_tran_checkbox_clicked(bool checked);
    void on_tran_button_pron_clicked();
    void on_dict_button_add_clicked();
    void on_tabWidget_main_tabBarClicked(int index);
    void on_tab_note_button_card_clicked();
    void on_tab_note_button_list_clicked();
    void on_tab_note_button_review_clicked();
};

#endif // MAINWINDOW_H
