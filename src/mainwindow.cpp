#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesignatureinfo.hpp"
#include "treeview.h"
#include "abstractfile.h"
#include "realfile.h"
#include "treepackagedragdropmodel.h"
#include "scripteditortabwidget.h"
#include "controlfileeditor.h"
#include "menufile.h"
#include "menuhelp.h"
#include <QListView>
#include <QGridLayout>
#include <QSplitter>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

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
    connect(menuFile, SIGNAL(wantScript(QString)), tabWidget, SLOT(addScriptEdit(QString)));
    connect(menuFile, SIGNAL(wantScript(QString)), treeView->model(), SLOT(addScriptFile(QString)));
    connect(menuFile, SIGNAL(wantDesktop(QString)), tabWidget, SLOT(addDesktopEdit()));
    connect(menuFile, SIGNAL(wantDesktop(QString)), treeView->model(), SLOT(addDesktopFile(QString)));
    connect(treeView->model(), SIGNAL(changeDesktopTab(QString, QString)), tabWidget, SLOT(renameDesktopTab(QString,QString)));

    connect(menuFile, SIGNAL(savePackageProject()), this, SLOT(saveToJson()));
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

void MainWindow::saveToJson()
{
    QJsonObject mainInfo;
    mainInfo.insert("package", QJsonValue::fromVariant(tabWidget->getControlFile()->getPackageName()));
    mainInfo.insert("version", QJsonValue::fromVariant(tabWidget->getControlFile()->getVersion()));
    mainInfo.insert("control", QJsonValue::fromVariant(tabWidget->getControlFile()->toPlainText()));

    QJsonObject scriptObject;
    for (CodeEditor *ce : tabWidget->getScriptTabs()){
        int idx = tabWidget->indexOf(ce);
        if (idx != -1){
            scriptObject.insert(tabWidget->tabText(idx), QJsonValue::fromVariant(ce->toPlainText()));
        }
    }
    mainInfo.insert("script", scriptObject);

    /*QJsonObject treeObject;
    auto treeModel = dynamic_cast<TreePackageDragDropModel*>(treeView->model());
    for (RealFile *rf : treeModel->getFileFromUser()){
        QString treePath;
        AbstractFile *parent = rf;
        while (parent->getParent() != nullptr){
            treePath.prepend(QString(parent->getParent()->getName().c_str())+"/");
            parent = parent->getParent();
        }
        treePath.chop(1); // remove last '/'
        treeObject.insert(treePath, rf->getFileSignatureInfo().getPath().c_str());
    }
    mainInfo.insert("tree", treeObject);*/

    QJsonDocument jsonDoc(mainInfo);
    QFile file(tabWidget->getControlFile()->getPackageName()+"-"+tabWidget->getControlFile()->getVersion()+".json");
    if (file.open(QIODevice::WriteOnly)){
        file.write(jsonDoc.toJson());
        file.close();
    }
}
