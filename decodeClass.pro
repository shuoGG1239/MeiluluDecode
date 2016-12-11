#-------------------------------------------------
#
# Project created by QtCreator 2016-12-03T22:08:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = decodeClass
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    decode.cpp \
    meiluludecode.cpp

HEADERS  += widget.h \
    decode.h \
    meiluludecode.h

FORMS    += widget.ui
