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
#include "NetworkController.h"
#include "dict_tran.h"
#include "dict.h"
#include "capture.h"
#include "dictbean.h"
#include "dict_simpbean.h"
#include "dict_webbean.h"
#include "dict_phrasebean.h"
#include "dict_examplebean.h"
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
    dict*dictTab;
public slots:


private slots:


    void on_dict_button_back_clicked();
    void on_dict_find_clicked();
    void on_dict_doc_clicked();
    void on_dict_shot_clicked();
};

#endif // MAINWINDOW_H
