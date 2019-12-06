#ifndef DICT_H
#define DICT_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include <CustomTabStyle.cpp>
#include <QFileDialog>
#include "NetworkController.h"
#include "dict_tran.h"
namespace Ui {
class dict;
}

class dict : public QWidget
{
    Q_OBJECT

public:
    explicit dict(QWidget *parent = 0);
    ~dict();

    dict_tran* dictTran;

private:
    Ui::dict *ui;

public slots:
    void requestFinished(QNetworkReply* reply);

private slots:

    void on_dict_find_clicked();
};

#endif // DICT_H
