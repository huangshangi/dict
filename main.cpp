#include "mainwindow.h"
#include "dict_note_add_window.h"
#include "dict_preference_window.h"
#include <QApplication>
#include <networkcontroller.h>
#include "config.h"
#include "languagewindow.h"
#include "settings.h"
#include "settingwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    groupmanagment w;

    w.show();


    return a.exec();
}
