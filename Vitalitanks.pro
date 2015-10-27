#-------------------------------------------------
#
# Project created by QtCreator 2015-10-27T01:37:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Vitalitanks
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    lib2d.cpp \
    Fonts.c

HEADERS  += mainwindow.h \
    Fonts.h \
    game.h \
    lib2d.h \
    point2di.h \
    node.h \
    line.h \
    material.h

FORMS    += mainwindow.ui
