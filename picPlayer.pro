#-------------------------------------------------
#
# Project created by QtCreator 2016-06-19T15:25:11
#
#-------------------------------------------------

QT       += core gui
QT      += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = picPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    piccache.cpp

HEADERS  += mainwindow.h \
    piccache.h



FORMS += \
    mainwindow.ui

RESOURCES += \
    img.qrc
