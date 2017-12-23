#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

class Folder;
class FileSignatureInfo;

class TreePackageModel : public QAbstractItemModel
{

    Q_OBJECT
public:
    TreePackageModel(QObject *parent = Q_NULLPTR);
    ~TreePackageModel();
    virtual QModelIndex	index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex &index) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual int	rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int	columnCount(const QModelIndex &parent = QModelIndex()) const;
    void addFileSignatureInfo(FileSignatureInfo *fsi);

private:
    virtual QVariant displayRole(const QModelIndex &index) const;
    virtual QVariant decorationRole(const QModelIndex &index) const;
    Folder *tree;

};

#endif // TREEMODEL_H
