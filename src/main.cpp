#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef USE_TERMUX_PATH
    qInfo() << "USE_TERMUX_PATH";
#endif

    MainWindow w;
    w.show();

    return a.exec();
}
