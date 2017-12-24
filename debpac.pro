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
    src/tabwidget.cpp \
    src/treepackagedrapdropmodel.cpp \
    src/syntaxhighlighter.cpp

HEADERS  += include/mainwindow.h \
    include/filesignatureinfo.hpp \
    include/treeview.h \
    include/abstractfile.h \
    include/realfile.h \
    include/folder.h \
    include/tabwidget.h \
    include/treepackagedragdropmodel.h \
    include/syntaxhighlighter.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc \
    default_file.qrc
