#ifndef LISTFILEMODEL_H
#define LISTFILEMODEL_H

#include <QAbstractListModel>
#include <QList>

class FileSignatureInfo;

class ListFileModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ListFileModel(QObject *parent = Q_NULLPTR);
    ~ListFileModel();
    void addFileInfo(FileSignatureInfo *fsi);
    void delFileInfo(int row);
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual int	rowCount(const QModelIndex &parent = QModelIndex()) const;

private:
    virtual QVariant displayRole(const QModelIndex &index) const;
    virtual QVariant decorationRole(const QModelIndex &index) const;
    QList<FileSignatureInfo*> info_files;
};

#endif // LISTFILEMODEL_H
