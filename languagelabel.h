#ifndef LANGUAGELABEL_H
#define LANGUAGELABEL_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
class languageLabel:public QPushButton
{
public:
    languageLabel(QString s,QWidget*parent=nullptr);


private:
    QPushButton*button;
};

#endif // LANGUAGELABEL_H
