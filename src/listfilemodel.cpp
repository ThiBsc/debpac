#include "../include/listfilemodel.h"
#include "../include/filesignatureinfo.hpp"
#include <QFileInfo>
#include <QIcon>

ListFileModel::ListFileModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

ListFileModel::~ListFileModel()
{
    for (FileSignatureInfo* fsi : info_files)
        delete fsi;
    info_files.clear();
}

QVariant ListFileModel::data(const QModelIndex &index, int role) const
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

void ListFileModel::addFileInfo(FileSignatureInfo *fsi)
{
    info_files.append(fsi);
}

int ListFileModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return info_files.size();
}

QVariant ListFileModel::displayRole(const QModelIndex &index) const
{
    FileSignatureInfo *fsi = info_files.at(index.row());
    QString ret;
    ret = QFileInfo(QString(fsi->getPath().c_str())).completeBaseName()+"\n";
    ret += QString(fsi->getExtension().c_str());
    return ret;
}

QVariant ListFileModel::decorationRole(const QModelIndex &index) const
{
    FileSignatureInfo *fsi = info_files.at(index.row());
    QIcon ret;
    switch (fsi->getCategory()) {
    case FileSignatureInfo::BINARY:
        ret = QIcon("://icon/binary.png");
        break;
    case FileSignatureInfo::AUDIO:
        ret = QIcon("://icon/audio.png");
        break;
    case FileSignatureInfo::PACKAGE:
        ret = QIcon("://icon/package.png");
        break;
    case FileSignatureInfo::IMAGE:
        ret = QIcon("://icon/image.png");
        break;
    default:
        break;
    }
    return ret;
}
