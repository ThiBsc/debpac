#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/filesignatureinfo.hpp"
#include "../include/treeview.h"
#include "../include/tabwidget.h"
#include <QListView>
#include <QGridLayout>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Debian package helper");
    setWindowIcon(QIcon("://icon/package.png"));
    gLayout = new QGridLayout(ui->centralWidget);
    ui->centralWidget->setLayout(gLayout);

    splitter = new QSplitter(Qt::Horizontal, this);
    tabWidget = new TabWidget(this);
    treeView = new TreeView(this);

    splitter->addWidget(treeView);
    splitter->addWidget(tabWidget);
    gLayout->addWidget(splitter, 0, 0);
}

MainWindow::~MainWindow()
{
    delete treeView;
    delete tabWidget;
    delete splitter;
    delete gLayout;
    delete ui;
}
