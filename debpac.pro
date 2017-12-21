#-------------------------------------------------
#
# Project created by QtCreator 2017-12-21T21:29:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = debpac
TEMPLATE = app


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/listfilemodel.cpp \
    src/filesignatureinfo.cpp

HEADERS  += include/mainwindow.h \
    include/listfilemodel.h \
    include/filesignatureinfo.hpp

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc
