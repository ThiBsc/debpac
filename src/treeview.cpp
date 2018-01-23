#include "treeview.h"
#include "treepackagedragdropmodel.h"
#include "filesignatureinfo.hpp"
#include "realfile.h"
#include <QMenu>
#include <QContextMenuEvent>

TreeView::TreeView(QWidget *parent)
    : QTreeView(parent)
{
    actionCreateFolder = new QAction("Create folder", this);
    actionRemoveFolder = new QAction("Remove folder", this);

    actionCreateFolder->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N));
    actionRemoveFolder->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_R));

    addAction(actionCreateFolder);
    addAction(actionRemoveFolder);

    tp_model = new TreePackageDragDropModel(this);
    setModel(tp_model);
    expandAll();
    setAcceptDrops(true);
    setDragEnabled(true);

    connect(actionCreateFolder, SIGNAL(triggered(bool)), this, SLOT(createFolder()));
    connect(actionRemoveFolder, SIGNAL(triggered(bool)), this, SLOT(removeFolder()));
}

TreeView::~TreeView()
{
    delete actionCreateFolder;
    delete actionRemoveFolder;
    delete tp_model;
}

void TreeView::addFile(FileSignatureInfo *fsi)
{
    tp_model->addFileInfo(fsi);
}

void TreeView::createFolder()
{
    tp_model->createFolder(currentIndex());
}

void TreeView::removeFolder()
{
    AbstractFile *af = static_cast<AbstractFile*>(currentIndex().internalPointer());
    if (af->getParent()->getParent() != nullptr){
        tp_model->removeFolder(currentIndex());
    }
}

void TreeView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (index.isValid()){
        AbstractFile *af = static_cast<AbstractFile*>(index.internalPointer());
        if (af->getName() != "DEBIAN" && af->getParent()->getName() != "DEBIAN"){
            // you can't touch DEBIAN folder
            QMenu menu(this);
            menu.addAction(actionCreateFolder);
            if (af->getParent()->getParent() != nullptr){
                // if is not DEBIAN or usr folder
                menu.addAction(actionRemoveFolder);
            }
            menu.exec(event->globalPos());
        }
    }
}

