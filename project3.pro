#-------------------------------------------------
#
# Project created by QtCreator 2016-06-14T01:20:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    item.cpp \
    land.cpp \
    bird.cpp \
    object.cpp \
    collisioncontecter.cpp \
    lv0.cpp \
    accelerator.cpp \
    piggie.cpp

HEADERS  += mainwindow.h \
    item.h \
    land.h \
    bird.h \
    object.h \
    collisioncontecter.h \
    lv0.h \
    accelerator.h \
    piggie.h

FORMS    += mainwindow.ui

LIBS += -lBox2D

RESOURCES += \
    resource.qrc

DISTFILES +=
