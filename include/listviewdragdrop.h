#ifndef LISTVIEWDRAGDROP_H
#define LISTVIEWDRAGDROP_H

#include <QListView>

class ListFileModel;
class FileSignatureInfo;

class ListViewDragDrop : public QListView
{
    Q_OBJECT
public:
    ListViewDragDrop(QWidget *parent = Q_NULLPTR);
    ~ListViewDragDrop();
    void addFileInfo(FileSignatureInfo *fsi);
    void delFileInfo(int row);

private:
    ListFileModel *lf_model;
};

#endif // LISTVIEWDRAGDROP_H
