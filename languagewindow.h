#ifndef LANGUAGEWINDOW_H
#define LANGUAGEWINDOW_H

#include <QWidget>

namespace Ui {
class languagewindow;
}

class languagewindow : public QWidget
{
    Q_OBJECT

public:
    explicit languagewindow(QWidget *parent = 0);
    ~languagewindow();

private:
    Ui::languagewindow *ui;
};

#endif // LANGUAGEWINDOW_H
