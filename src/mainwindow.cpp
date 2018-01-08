#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filesignatureinfo.hpp"
#include "treeview.h"
#include "abstractfile.h"
#include "realfile.h"
#include "folder.h"
#include "treepackagedragdropmodel.h"
#include "scripteditortabwidget.h"
#include "controlfileeditor.h"
#include "menufile.h"
#include "menuhelp.h"
#include "processdpkgdeb.h"
#include <QListView>
#include <QGridLayout>
#include <QSplitter>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileDialog>
#include <QProcess>

const QString MainWindow::version = "0.68";

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

    connect(menuFile, SIGNAL(wantGeneratePackage()), this, SLOT(generatePackage()));
    connect(menuFile, SIGNAL(savePackageProject()), this, SLOT(saveToJson()));
    connect(menuFile, SIGNAL(importPackageProject()), this, SLOT(restoreFromJson()));
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
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save state"),
                                                    tabWidget->getControlFile()->getPackageName()+"-"+tabWidget->getControlFile()->getVersion()+".json",
                                                    tr("Json file (*.json)"));
    if (!fileName.isNull()){
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

        QJsonObject treeObject;
        auto treeModel = dynamic_cast<TreePackageDragDropModel*>(treeView->model());
        for (RealFile *rf : treeModel->getFileFromUser()){
            QString treePath;
            AbstractFile *parent = rf->getParent();
            while (parent->getParent() != nullptr){
                treePath.prepend(QString(parent->getName().c_str())+"/");
                parent = parent->getParent();
            }
            treePath.chop(1); // remove last '/'
            treeObject.insert(treePath, QJsonValue::fromVariant(rf->getFileSignatureInfo().getPath().c_str()));
        }
        mainInfo.insert("tree", treeObject);

        QJsonDocument jsonDoc(mainInfo);
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)){
            file.write(jsonDoc.toJson());
            file.close();
        }
    }
}

void MainWindow::restoreFromJson()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load file"), QString(), tr("Json files (*.json);;All files (*.*)"));
    if (!fileName.isNull()){
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)){
            QJsonDocument json_doc(QJsonDocument::fromJson(file.readAll()));
            file.close();
            if (!json_doc.isNull()){
                QJsonObject json_obj = json_doc.object();
                if (!json_obj.isEmpty()){
                    // the file and content will be ok... reset before import
                    auto treeModel = dynamic_cast<TreePackageDragDropModel*>(treeView->model());
                    treeModel->resetToDefault();
                    tabWidget->resetToDefault();

                    const QString package = json_obj.take("package").toString();
                    const QString version = json_obj.take("version").toString();
                    const QString control = json_obj.take("control").toString();
                    tabWidget->getControlFile()->setPackageName(package);
                    tabWidget->getControlFile()->setVersion(version);
                    tabWidget->getControlFile()->setPlainText(control);

                    QJsonObject scripts = json_obj.take("script").toObject();
                    for (QString key : scripts.keys()){
                        int tab_idx = -1;
                        if (key.contains(".desktop")){
                            tab_idx = tabWidget->addDesktopEdit();
                            treeModel->addDesktopFile(key);
                        } else {
                            tab_idx = tabWidget->addScriptEdit(key);
                            treeModel->addScriptFile(key);
                        }
                        if (tab_idx)
                            dynamic_cast<CodeEditor*>(tabWidget->widget(tab_idx))->setPlainText(scripts.take(key).toString());
                    }

                    QJsonObject tree = json_obj.take("tree").toObject();
                    for (QString key : tree.keys()){
                        const QString file_info = tree.take(key).toString();
                        FileSignatureInfo *fsi = new FileSignatureInfo(file_info.toStdString());
                        if (fsi->getCategory() == FileSignatureInfo::INEXISTANT){
                            delete fsi;
                        } else {
                            treeModel->addFileInfo(key, fsi);
                        }
                    }
                    treeView->expandAll();
                }
            }
        }
    }
}

#include <QDebug>
void MainWindow::generatePackage()
{

    QString deb_name = tabWidget->getControlFile()->getPackageName() + "-" + tabWidget->getControlFile()->getVersion() + ".deb";
    deb_name = QFileDialog::getSaveFileName(this, tr("Generate package"), deb_name, tr(".deb file (*.deb)"));
    if (!deb_name.isNull()){
        auto treeModel = dynamic_cast<TreePackageDragDropModel*>(treeView->model());
        Folder *root = treeModel->getRoot();
        const QString tmp = QDir::tempPath();
        QDir dir_package(tmp);
        if (dir_package.mkdir(root->getName().c_str())){
            if (dir_package.cd(root->getName().c_str())){
                // create the control file
                if (dir_package.mkpath("DEBIAN")){
                    QFile file(dir_package.filePath("DEBIAN/control"));
                    if (file.open(QIODevice::WriteOnly)){
                        // the control file has no comment, so remove it
                        QString clean_control = "";
                        for (QString line : tabWidget->getControlFile()->toPlainText().split("\n")){
                            if (!line.startsWith('#'))
                                clean_control.append(line+"\n");
                        }
                        file.write(clean_control.toStdString().c_str());
                        file.close();
                    }
                }
                // create the script files
                QList<RealFile*> files_list = treeModel->getFileFromProgram();
                for (RealFile *f : files_list){
                    QString fPath;
                    AbstractFile *parent = f->getParent();
                    while (parent->getParent() != nullptr){
                        fPath.prepend(QString(parent->getName().c_str())+"/");
                        parent = parent->getParent();
                    }
                    if (dir_package.mkpath(fPath)){
                        QFile file(dir_package.filePath(fPath+f->getName().c_str()));
                        if (file.open(QIODevice::WriteOnly)){
                            int tab_idx = tabWidget->getIndexByName(f->getName().c_str());
                            if (tab_idx != -1){
                                file.write(dynamic_cast<CodeEditor*>(tabWidget->widget(tab_idx))->toPlainText().toStdString().c_str());
                                file.close();
                                QProcess *chmod = new QProcess(this);
                                chmod->start("chmod", QStringList() << "755" << file.fileName());
                                chmod->waitForFinished(-1);
                                delete chmod;
                            }
                        }
                    }
                }
                // copy the user files
                files_list = treeModel->getFileFromUser();
                for (RealFile *f : files_list){
                    QString fPath;
                    AbstractFile *parent = f->getParent();
                    while (parent->getParent() != nullptr){
                        fPath.prepend(QString(parent->getName().c_str())+"/");
                        parent = parent->getParent();
                    }
                    if (dir_package.mkpath(fPath)){
                        const QString origin = f->getFileSignatureInfo().getPath().c_str();
                        QFile::copy(origin, dir_package.filePath(fPath+QFileInfo(origin).fileName()));
                    }
                }
                // now generate using dpkg-deb --build package_name
                ProcessDpkgdeb *dpkg_deb = new ProcessDpkgdeb(this);
                dpkg_deb->start("gksudo", QStringList() << QString("dpkg-deb --build %1 %2").arg(tmp+"/"+tabWidget->getControlFile()->getPackageName()).arg(deb_name));
                dpkg_deb->waitForFinished(-1);
                delete dpkg_deb;
            }
        }
    }
}
