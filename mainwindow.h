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
#include "NetworkController.h"
#include "dict_tran.h"
#include "dict.h"
#include "capture.h"
#include "dictbean.h"
#include "dict_simpbean.h"
#include "dict_webbean.h"
#include "dict_phrasebean.h"
#include "dict_examplebean.h"

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

private:
    Ui::MainWindow *ui;

public slots:


private slots:

    void playAudio(QNetworkReply*reply);
    void on_dict_button_back_clicked();
    void on_dict_find_clicked();
    void on_dict_doc_clicked();
    void on_dict_shot_clicked();
    void on_dict_button_pron_clicked();
    void on_dict_button_find_clicked();
    void on_tran_edit_from_textChanged();
    void on_tran_button_clear_clicked();
};

#endif // MAINWINDOW_H
