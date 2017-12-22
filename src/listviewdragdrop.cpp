#include "../include/listviewdragdrop.h"
#include "../include/listfilemodel.h"

ListViewDragDrop::ListViewDragDrop(QWidget *parent)
    : QListView(parent)
{
    model = new ListFileModel(this);
    setModel(model);
    setAcceptDrops(true);
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

