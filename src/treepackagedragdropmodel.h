#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>

class Folder;
class RealFile;
class FileSignatureInfo;

/**
 * @brief The TreePackageDragDropModel class
 * The model used in the TreeView to manage file by drag & drop
 */

class TreePackageDragDropModel : public QAbstractItemModel
{

    Q_OBJECT
public:
    TreePackageDragDropModel(QObject *parent = Q_NULLPTR);
    ~TreePackageDragDropModel();
    void resetToDefault();
    virtual QModelIndex	index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;
    virtual QModelIndex	parent(const QModelIndex &index) const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
    virtual bool canDropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    virtual Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual int	rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual int	columnCount(const QModelIndex &parent = QModelIndex()) const;
    void addFileInfo(FileSignatureInfo *fsi);
    void addFileInfo(const QString& path, FileSignatureInfo *fsi);
    QVector<RealFile *> getFileFromUser();
    QVector<RealFile *> getFileFromProgram();
    Folder *getRoot();

public slots:
    void addScriptFile(const QString& name);
    void addDesktopFile(const QString& name);
    void changePackageName(const QString &pname);
    void createFolder(const QModelIndex &index);
    void removeFolder(const QModelIndex &index);

signals:
    void changeDesktopTab(const QString &oldname, const QString &newname);

private:
    virtual QVariant displayRole(const QModelIndex &index) const;
    virtual QVariant decorationRole(const QModelIndex &index) const;
    Folder *tree;
    QVector<RealFile*> fileFromUser;
    QVector<RealFile*> fileFromProgram;

};

#endif // TREEMODEL_H
