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
    src/filesignatureinfo.cpp \
    src/listviewdragdrop.cpp \
    src/treeview.cpp \
    src/treepackagemodel.cpp \
    src/abstractfile.cpp \
    src/realfile.cpp \
    src/folder.cpp

HEADERS  += include/mainwindow.h \
    include/listfilemodel.h \
    include/filesignatureinfo.hpp \
    include/listviewdragdrop.h \
    include/treeview.h \
    include/treepackagemodel.h \
    include/abstractfile.h \
    include/realfile.h \
    include/folder.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc
