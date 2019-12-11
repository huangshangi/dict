#ifndef DICT_NOTE_ADD_WINDOW_H
#define DICT_NOTE_ADD_WINDOW_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QMainWindow>
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

private slots:
    void on_button_sure_clicked();

    void on_button_cancel_clicked();

private:
    Ui::dict_note_add_window *ui;
};

#endif // DICT_NOTE_ADD_WINDOW_H
