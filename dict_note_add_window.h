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
namespace Ui {
class dict_note_add_window;
}

class dict_note_add_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit dict_note_add_window(QWidget *parent = 0);
    ~dict_note_add_window();

private slots:
    void on_button_sure_clicked();

private:
    Ui::dict_note_add_window *ui;
};

#endif // DICT_NOTE_ADD_WINDOW_H
