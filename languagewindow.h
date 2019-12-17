#ifndef LANGUAGEWINDOW_H
#define LANGUAGEWINDOW_H

#include <QWidget>
#include "languagelabel.h"
#include <QDebug>
#include <QMouseEvent>
#include <QString>
#include <QStringList>
#include <QTableWidgetItem>
#include <QEvent>
namespace Ui {
class languagewindow;
}

class languagewindow : public QWidget
{
    Q_OBJECT

public:
    explicit languagewindow(QWidget *parent = 0);
    ~languagewindow();
    bool eventFilter(QObject *watched, QEvent *e);

    bool event(QEvent *event);

    void initList();

    void initUi();

    void button_from_click();

    void button_to_click();
private slots:
    void common_click();

    void assign_click();

    void on_button_from_clicked();

    void on_button_to_clicked();

private:
    Ui::languagewindow *ui;
    QPushButton *fromButton;
    QPushButton *toButton;

    int state;//0->下拉框未出现 1->from下拉框  2->to下拉框

    QStringList list_common;
    QStringList list_assign;

private:
    void strechWindow();

private:
    int findInList(QString value,QStringList);
};

#endif // LANGUAGEWINDOW_H
