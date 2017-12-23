#include "../include/treeview.h"
#include "../include/treepackagemodel.h"
#include "../include/filesignatureinfo.hpp"

TreeView::TreeView(QWidget *parent)
    : QTreeView(parent)
{
    tp_model = new TreePackageModel(this);
    setModel(tp_model);
    expandAll();}

TreeView::~TreeView()
{
    delete tp_model;
}

void TreeView::addFile(FileSignatureInfo *fsi)
{
    tp_model->addFileSignatureInfo(fsi);
}

