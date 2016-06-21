#-------------------------------------------------
#
# Project created by QtCreator 2016-02-24T13:47:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    log_in.cpp \
    registration.cpp \
    mainbook.cpp \
    clientsocket.cpp \
    buy_books.cpp

HEADERS  += mainwindow.h \
    log_in.h \
    registration.h \
    mainbook.h \
    clientsocket.h \
    buy_books.h

FORMS    += mainwindow.ui \
    log_in.ui \
    registration.ui \
    mainbook.ui \
    buy_books.ui

RESOURCES += \
    image.qrc

DISTFILES +=
LIBS += -lws2_32
