#include "mainwindow.h"
#include "dict_note_add_window.h"
#include <QApplication>
#include <networkcontroller.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dict_note_add_window w;
    w.show();


    return a.exec();
}
