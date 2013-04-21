#-------------------------------------------------
#
# Project created by QtCreator 2012-11-09T17:57:16
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SWAnnabaTimer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    quotes.cpp \
    swtimer.cpp

HEADERS  += mainwindow.h \
    quotes.h \
    swtimer.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

RC_FILE = app.rc
