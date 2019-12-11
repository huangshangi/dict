#-------------------------------------------------
#
# Project created by QtCreator 2019-12-04T12:45:54
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
QT       += widgets
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dict
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    settingwindow.cpp \
    networkcontroller.cpp \
    customtabstyle.cpp \
    youdaotranslator.cpp \
    capture.cpp \
    dictbean.cpp \
    dict_simpbean.cpp \
    dict_webbean.cpp \
    dict_phrasebean.cpp \
    dict_examplebean.cpp \
    tranbean.cpp \
    connectpool.cpp \
    newwordbean.cpp \
    databasecontroller.cpp \
    dict_edit.cpp \
    groupmanagment.cpp \
    dict_note_add_window.cpp \
    dict_preference_window.cpp \
    config.cpp \
    languagewindow.cpp \
    settings.cpp

HEADERS += \
        mainwindow.h \
    settingwindow.h \
    networkcontroller.h \
    youdaotranslator.h \
    capture.h \
    jsonpaser.h \
    dictbean.h \
    dict_simpbean.h \
    dict_webbean.h \
    dict_phrasebean.h \
    dict_examplebean.h \
    tranbean.h \
    connectpool.h \
    newwordbean.h \
    databasecontroller.h \
    dict_edit.h \
    groupmanagment.h \
    dict_note_add_window.h \
    dict_preference_window.h \
    config.h \
    languagewindow.h \
    settings.h

FORMS += \
        mainwindow.ui \
    settingwindow.ui \
    capture.ui \
    dict_edit.ui \
    groupmanagment.ui \
    dict_note_add_window.ui \
    dict_preference_window.ui \
    languagewindow.ui
