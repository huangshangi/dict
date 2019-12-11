#include "mainwindow.h"
#include "dict_note_add_window.h"
#include <QApplication>
#include <networkcontroller.h>
#include "config.h"
#include "languagewindow.h"
#include "settings.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    settings* setting=settings::getInstance();
    qDebug()<<setting->getFont();
    return a.exec();
}
