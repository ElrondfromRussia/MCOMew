#-------------------------------------------------
#
# Project created by QtCreator 2019-03-22T11:48:38
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MCOMew
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    +=

RESOURCES += \
    res.qrc

DISTFILES += \
    myapp.rc

win32: RC_FILE = myapp.rc
