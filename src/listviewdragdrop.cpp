#include "../include/listviewdragdrop.h"
#include "../include/listfilemodel.h"

ListViewDragDrop::ListViewDragDrop(QWidget *parent)
    : QListView(parent)
{
    lf_model = new ListFileModel(this);
    setModel(lf_model);
    setAcceptDrops(true);
}

ListViewDragDrop::~ListViewDragDrop()
{
    delete lf_model;
}

void ListViewDragDrop::addFileInfo(FileSignatureInfo *fsi)
{
    lf_model->addFileInfo(fsi);
}

void ListViewDragDrop::delFileInfo(int row)
{
    lf_model->delFileInfo(row);
}

