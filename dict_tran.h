#ifndef DICT_TRAN_H
#define DICT_TRAN_H

#include <QWidget>

namespace Ui {
class dict_tran;
}

class dict_tran : public QWidget
{
    Q_OBJECT

public:
    explicit dict_tran(QWidget *parent = 0);
    ~dict_tran();

private:
    Ui::dict_tran *ui;
};

#endif // DICT_TRAN_H
