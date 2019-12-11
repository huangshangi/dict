#ifndef LANGUAGEWINDOW_H
#define LANGUAGEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
namespace Ui {
class languagewindow;
}

class languagewindow : public QWidget
{
    Q_OBJECT

public:
    explicit languagewindow(QWidget *parent = 0);
    ~languagewindow();

private slots:
    void on_label_2_linkHovered(const QString &link);

    void on_label_2_linkActivated(const QString &link);

private:
    Ui::languagewindow *ui;
};

#endif // LANGUAGEWINDOW_H
