#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

class Folder;
class FileSignatureInfo;

class TreePackageDragDropModel : public QAbstractItemModel
{

    Q_OBJECT
public:
    TreePackageDragDropModel(QObject *parent = Q_NULLPTR);
    ~TreePackageDragDropModel();
    virtual QModelIndex	index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex &index) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;    
    virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual int	rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int	columnCount(const QModelIndex &parent = QModelIndex()) const;
    void addFileInfo(FileSignatureInfo *fsi);

public slots:
    void changePackageName(const QString &pname);

private:
    virtual QVariant displayRole(const QModelIndex &index) const;
    virtual QVariant decorationRole(const QModelIndex &index) const;
    Folder *tree;

};

#endif // TREEMODEL_H
