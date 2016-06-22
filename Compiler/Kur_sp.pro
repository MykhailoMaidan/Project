#-------------------------------------------------
#
# Project created by QtCreator 2015-11-23T16:28:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kur_sp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    compiler.cpp

HEADERS  += mainwindow.h \
    compiler.h

FORMS    += mainwindow.ui
CONFIG += c++11
