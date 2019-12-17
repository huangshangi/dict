#include "languagelabel.h"



languageLabel::languageLabel(QString s, QWidget *parent)
{
    button=new QPushButton(parent);
    button->setText(s);
    button->setStyleSheet("QPushButton{text-align:left;background-color:transparent;border:none;}"
                          "QPushButton:hover{color:#f00;background-color:transparent;text-align:left;border:none;}");

    //button->setSizeIncrement();
    QHBoxLayout*layout=new QHBoxLayout;
    layout->addWidget(button);
    setLayout(layout);
}
