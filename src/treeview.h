#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

class TreePackageDragDropModel;
class FileSignatureInfo;

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget *parent = Q_NULLPTR);
    ~TreeView();

public slots:
    void addFile(FileSignatureInfo *fsi);

private:
    TreePackageDragDropModel *tp_model;

};

#endif // TREEVIEW_H
