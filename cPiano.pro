#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T15:54:50
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cPiano
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

RESOURCES += \
    resources.qrc
