#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/listviewdragdrop.h"
#include "../include/filesignatureinfo.hpp"
#include "../include/treeview.h"
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
    treeView = new TreeView(this);

    gLayout->addWidget(listView, 0, 0);
    gLayout->addWidget(treeView, 0, 1);

    connect(listView->model(), SIGNAL(fileSignatureInfoAdded(FileSignatureInfo*)), treeView, SLOT(addFile(FileSignatureInfo*)));
}

MainWindow::~MainWindow()
{
    delete treeView;
    delete listView;
    delete gLayout;
    delete ui;
}
