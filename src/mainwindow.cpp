#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/listfilemodel.h"
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

    listFileView = new QListView(this);
    listModel = new ListFileModel(listFileView);
    listFileView->setModel(listModel);

    listModel->addFileInfo(new FileSignatureInfo("/home/thibaut/programmation/qt/build-RegExptestor-Desktop_Qt_5_5_1_GCC_64bit2-Release/regexp_testor"));
    listModel->addFileInfo(new FileSignatureInfo("/home/thibaut/Téléchargements/atom-amd64.deb"));
    listModel->addFileInfo(new FileSignatureInfo("/home/thibaut/programmation/qt/debpac/icon/package.png"));

    gLayout->addWidget(listFileView, 0, 0);
}

MainWindow::~MainWindow()
{
    delete listModel;
    delete listFileView;
    delete gLayout;
    delete ui;
}
