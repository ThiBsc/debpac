#include "treepackagedragdropmodel.h"
#include "folder.h"
#include "realfile.h"
#include "filesignatureinfo.hpp"
#include <QIcon>
#include <QFileInfo>
#include <QMimeData>
#include <QUrl>

TreePackageDragDropModel::TreePackageDragDropModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    // default tree of a debian package
    tree = new Folder("package_name");
    tree->add(new Folder("DEBIAN")).add(new RealFile("control"));
    tree->add(new Folder("usr")).add(new Folder("bin"));
}

TreePackageDragDropModel::~TreePackageDragDropModel()
{
    delete tree;
}

QModelIndex TreePackageDragDropModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex ret;
    if (hasIndex(row, column, parent)){
        AbstractFile *parentItem;
        if (parent.isValid()){
            parentItem = static_cast<AbstractFile*>(parent.internalPointer());
        } else {
            parentItem = tree; // root
        }
        if(Folder* f = dynamic_cast<Folder*>(parentItem)) {
           ret = createIndex(row, column, f->child(row));
        }
    }
    return ret;
}

QModelIndex TreePackageDragDropModel::parent(const QModelIndex &index) const
{
    QModelIndex ret;
    if (index.isValid()){
        AbstractFile *child = static_cast<AbstractFile*>(index.internalPointer());
        AbstractFile *parent = child->getParent();
        if (parent && parent != child){
            ret = createIndex(1, 0, parent);
        }
    }
    return ret;
}

QVariant TreePackageDragDropModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;
    if (index.isValid()){
        switch (role) {
        case Qt::DisplayRole:
            ret = displayRole(index);
            break;
        case Qt::DecorationRole:
            ret = decorationRole(index);
            break;
        default:
            break;
        }
    }
    return ret;
}

QVariant TreePackageDragDropModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section);
    QVariant ret;
    if (orientation == Qt::Horizontal){
        switch (role) {
        case Qt::DisplayRole:
            ret = QString("Package name: %1").arg(tree->getName().c_str());
            break;
        default:
            break;
        }
    }
    return ret;
}

bool TreePackageDragDropModel::canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);
    bool ret = false;
    if (data->hasUrls()){
        ret = QFileInfo(data->urls().first().path()).isFile();
    }
    return ret;
}

bool TreePackageDragDropModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(action);
    Q_UNUSED(row);
    Q_UNUSED(column);
    Q_UNUSED(parent);
    bool ret = false;
    FileSignatureInfo *fsi = new FileSignatureInfo(data->urls().first().path().toStdString());
    int before = tree->count(true);
    addFileInfo(fsi);
    if (before < tree->count(true)){
        ret = true;
    } else {
        delete fsi;
    }
    return ret;
}

Qt::ItemFlags TreePackageDragDropModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags ret = QAbstractItemModel::flags(index);
    if (!index.isValid())
        ret |= Qt::ItemIsDropEnabled;
    return ret;
}

int TreePackageDragDropModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    int ret = 0;
    AbstractFile *parentItem = static_cast<AbstractFile*>(parent.internalPointer());
    if (parent.isValid()){
        if(Folder* f = dynamic_cast<Folder*>(parentItem)) {
            ret = f->count(false);
        } else {
            ret = 0;
        }
    } else {
        // root
        ret = tree->count(false);
    }
    return ret;
}

int TreePackageDragDropModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

void TreePackageDragDropModel::addFileInfo(FileSignatureInfo *fsi)
{
    QModelIndex parentIndex = index(0);
    QString folder;
    switch (fsi->getCategory()) {
    case FileSignatureInfo::BINARY:
        folder = "usr/bin";
        break;
    case FileSignatureInfo::AUDIO:
        folder = "usr/share/"+QString(tree->getName().c_str())+"/sounds";
        break;
    case FileSignatureInfo::IMAGE:
        if (QPixmap(fsi->getPath().c_str()).width() == QPixmap(fsi->getPath().c_str()).height()){
            folder = "usr/share/icons/hicolor/"+QString("%1x%1").arg(QPixmap(fsi->getPath().c_str()).width())+"/apps";
        } else {
            folder = "usr/share/"+QString(tree->getName().c_str())+"/images";
        }
        break;
    case FileSignatureInfo::PACKAGE:
    case FileSignatureInfo::ARCHIVE:
    default:
        folder = "usr/share/"+QString(tree->getName().c_str());
        break;
    }
    if (!folder.isEmpty()){
        QStringList sl = folder.split("/");
        Folder *f = tree;
        for (QString s : sl){
            if (Folder *current = f->getChild<Folder*>(s.toStdString())){
                f = current;
            } else {
                int at = f->count(false);
                beginInsertRows(parentIndex, at, at);
                Folder *nf = new Folder(s.toStdString());
                f->add(nf);
                f = nf;
                endInsertRows();
            }
            parentIndex = index(0, 0, parentIndex);
        }
        if (f){
            int at = f->count(false);
            beginInsertRows(parentIndex, at, at);
            f->add(new RealFile(QFileInfo(fsi->getPath().c_str()).completeBaseName().toStdString().c_str(), fsi));
            endInsertRows();
        }
    }
}

void TreePackageDragDropModel::addScriptFile(const QString &name)
{
    Folder *debian = tree->getChild<Folder*>("DEBIAN");
    if (debian){
        if (!debian->containFile(name.toStdString())){
            int at = debian->count(false);
            beginInsertRows(index(1), at, at);
            debian->add(new RealFile(name.toStdString()));
            endInsertRows();
        }
    }
}

void TreePackageDragDropModel::addDesktopFile(const QString &name)
{
    Q_UNUSED(name);
    QModelIndex parentIndex = index(0);
    QString folder = "usr/share/applications";
    QStringList sl = folder.split("/");
    Folder *f = tree;
    for (QString s : sl){
        if (Folder *current = f->getChild<Folder*>(s.toStdString())){
            f = current;
        } else {
            int at = f->count(false);
            beginInsertRows(parentIndex, at, at);
            Folder *nf = new Folder(s.toStdString());
            f->add(nf);
            f = nf;
            endInsertRows();
        }
        parentIndex = index(0, 0, parentIndex);
    }
    if (f && !f->containFile(tree->getName()+".desktop")){
        int at = f->count(false);
        beginInsertRows(parentIndex, at, at);
        f->add(new RealFile(tree->getName()+".desktop"));
        endInsertRows();
    }
}

void TreePackageDragDropModel::changePackageName(const QString &pname)
{
    if (Folder *apps_folder = tree->containFolder("applications", true)){
        if (RealFile *desktop = apps_folder->containFile(tree->getName()+".desktop")){
            desktop->setName(pname.toStdString()+".desktop");
            emit changeDesktopTab(tree->getName().c_str(), pname);
        }
    }
    tree->renameFolder(tree->getName(), pname.toStdString(), true);
    emit headerDataChanged(Qt::Horizontal, 0, 0);
}

QVariant TreePackageDragDropModel::displayRole(const QModelIndex &index) const
{
    QString ret = QString(static_cast<AbstractFile*>(index.internalPointer())->getName().c_str());
    return ret;
}

QVariant TreePackageDragDropModel::decorationRole(const QModelIndex &index) const
{
    QIcon ret;
    AbstractFile *af = static_cast<AbstractFile*>(index.internalPointer());
    if(dynamic_cast<Folder*>(af)) {
        ret = QIcon("://icon/folder.png");
    } else {
        ret = dynamic_cast<RealFile*>(af)->getFileSignatureInfo().getIcon();
    }
    return ret;
}
