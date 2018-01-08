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
    src/filesignatureinfo.cpp \
    src/treeview.cpp \
    src/abstractfile.cpp \
    src/realfile.cpp \
    src/folder.cpp \
    src/treepackagedrapdropmodel.cpp \
    src/syntaxhighlighter.cpp \
    src/scripteditortabwidget.cpp \
    src/linenumberarea.cpp \
    src/codeeditor.cpp \
    src/controlfileeditor.cpp \
    src/menufile.cpp \
    src/menuhelp.cpp \
    src/processdpkgdeb.cpp

HEADERS  += src/mainwindow.h \
    src/filesignatureinfo.hpp \
    src/treeview.h \
    src/abstractfile.h \
    src/realfile.h \
    src/folder.h \
    src/treepackagedragdropmodel.h \
    src/syntaxhighlighter.h \
    src/scripteditortabwidget.h \
    src/linenumberarea.h \
    src/codeeditor.h \
    src/controlfileeditor.h \
    src/menufile.h \
    src/menuhelp.h \
    src/processdpkgdeb.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc \
    default_file.qrc
