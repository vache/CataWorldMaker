#-------------------------------------------------
#
# Project created by QtCreator 2014-03-11T19:22:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CataWorldMaker
TEMPLATE = app


SOURCES += main.cpp\
        cataworldmaker.cpp \
    displaywidget.cpp \
    worldmodel.cpp \
    worldtile.cpp \
    tiletypemodel.cpp \
    overmapjsonreader.cpp

HEADERS  += cataworldmaker.h \
    displaywidget.h \
    worldmodel.h \
    worldtile.h \
    tiletypemodel.h \
    overmapjsonreader.h \
    colors.h

FORMS    += cataworldmaker.ui
