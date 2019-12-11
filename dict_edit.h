#ifndef DICT_EDIT_H
#define DICT_EDIT_H

#include <QMainWindow>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "databasecontroller.h"
#include "connectpool.h"
#include "newwordbean.h"
#include <QCloseEvent>
namespace Ui {
class dict_edit;
}

class dict_edit : public QMainWindow
{
    Q_OBJECT
signals:
    void updateList();
public:
    explicit dict_edit(QWidget *parent = 0);
    dict_edit(QWidget *parent ,QString name);
    ~dict_edit();

    QString getName() const;
    void setName(const QString &value);

    void closeEvent(QCloseEvent*closeEvent);

private slots:
    void on_dict_edit_button_dict_clicked();

    void on_dict_edit_button_sure_clicked();

    void on_dict_edit_button_cancel_clicked();

private:
    Ui::dict_edit *ui;
    QString name;
};

#endif // DICT_EDIT_H
