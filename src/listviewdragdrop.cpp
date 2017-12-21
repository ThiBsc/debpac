#include "../include/listviewdragdrop.h"
#include "../include/listfilemodel.h"

ListViewDragDrop::ListViewDragDrop(QWidget *parent)
    : QListView(parent)
{
    model = new ListFileModel(this);
    setModel(model);
}

ListViewDragDrop::~ListViewDragDrop()
{
    delete model;
}

void ListViewDragDrop::addFileInfo(FileSignatureInfo *fsi)
{
    model->addFileInfo(fsi);
}

void ListViewDragDrop::delFileInfo(int row)
{
    model->delFileInfo(row);
}

void ListViewDragDrop::dragLeaveEvent(QDragLeaveEvent *e)
{

}

void ListViewDragDrop::dragMoveEvent(QDragMoveEvent *e)
{

}

void ListViewDragDrop::dropEvent(QDropEvent *e)
{

}
