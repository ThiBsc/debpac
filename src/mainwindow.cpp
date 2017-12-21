#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/listviewdragdrop.h"
#include "../include/filesignatureinfo.hpp"
#include <QListView>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Debian package helper");
    setWindowIcon(QIcon("://icon/package.png"));
    gLayout = new QGridLayout(ui->centralWidget);
    ui->centralWidget->setLayout(gLayout);

    listView = new ListViewDragDrop(this);

    listView->addFileInfo(new FileSignatureInfo("/home/thibaut/programmation/qt/build-RegExptestor-Desktop_Qt_5_5_1_GCC_64bit2-Release/regexp_testor"));
    listView->addFileInfo(new FileSignatureInfo("/home/thibaut/Téléchargements/atom-amd64.deb"));
    listView->addFileInfo(new FileSignatureInfo("/home/thibaut/programmation/qt/debpac/icon/package.png"));
    listView->delFileInfo(1);
    listView->addFileInfo(new FileSignatureInfo("/home/thibaut/Téléchargements/atom-amd64.deb"));
    listView->delFileInfo(0);

    gLayout->addWidget(listView, 0, 0);
}

MainWindow::~MainWindow()
{
    delete listView;
    delete gLayout;
    delete ui;
}
