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

protected:
    virtual void dragLeaveEvent(QDragLeaveEvent *e);
    virtual void dragMoveEvent(QDragMoveEvent *e);
    virtual void dropEvent(QDropEvent *e);

private:
    ListFileModel *model;
};

#endif // LISTVIEWDRAGDROP_H
