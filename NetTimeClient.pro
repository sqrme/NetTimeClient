#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T10:20:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetTimeClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    configinfo.cpp \
    nettimeclient.cpp \
    netreceiver.cpp \
    log.cpp \
    timeadjuster.cpp

HEADERS  += mainwindow.h \
    configinfo.h \
    nettimeclient.h \
    netreceiver.h \
    log.h \
    timeadjuster.h \
    common.h

FORMS    += mainwindow.ui
