#include "treeview.h"
#include "treepackagedragdropmodel.h"
#include "filesignatureinfo.hpp"

TreeView::TreeView(QWidget *parent)
    : QTreeView(parent)
{
    tp_model = new TreePackageDragDropModel(this);
    setModel(tp_model);
    expandAll();
    setAcceptDrops(true);
}

TreeView::~TreeView()
{
    delete tp_model;
}

void TreeView::addFile(FileSignatureInfo *fsi)
{
    tp_model->addFileInfo(fsi);
}

