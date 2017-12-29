#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesignatureinfo.hpp"
#include "treeview.h"
#include "scripteditortabwidget.h"
#include "controlfileeditor.h"
#include "menufile.h"
#include "menuhelp.h"
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
    menuFile = new MenuFile(this);
    menuHelp = new MenuHelp(this);
    ui->menuBar->addMenu(menuFile);
    ui->menuBar->addMenu(menuHelp);
    for (QAction *a : menuFile->actions())
        ui->mainToolBar->addAction(a);

    gLayout = new QGridLayout(ui->centralWidget);
    ui->centralWidget->setLayout(gLayout);

    splitter = new QSplitter(Qt::Horizontal, this);
    tabWidget = new ScripEditorTabWidget(this);
    treeView = new TreeView(this);

    splitter->addWidget(treeView);
    splitter->addWidget(tabWidget);
    gLayout->addWidget(splitter, 0, 0);

    splitter->setStretchFactor(1, 2);
    resize(700, 400);

    connect(tabWidget->getControlFile(), SIGNAL(packageNameChanged(QString)), treeView->model(), SLOT(changePackageName(QString)));
}

MainWindow::~MainWindow()
{
    delete treeView;
    delete tabWidget;
    delete splitter;
    delete gLayout;
    delete menuFile;
    delete menuHelp;
    delete ui;
}
