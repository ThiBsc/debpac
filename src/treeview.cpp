#include "treeview.h"
#include "treepackagedragdropmodel.h"
#include "filesignatureinfo.hpp"
#include "realfile.h"
#include <QMenu>
#include <QContextMenuEvent>

TreeView::TreeView(QWidget *parent)
    : QTreeView(parent)
{
    actionUpFile = new QAction("Up file", this);
    actionDownFile = new QAction("Down file", this);
    actionCreateFolder = new QAction("Create folder", this);
    actionRenameFolder = new QAction("Rename folder", this);

    actionUpFile->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Up));
    actionDownFile->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Down));
    actionCreateFolder->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_N));
    actionRenameFolder->setShortcut(QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_R));

    addAction(actionUpFile);
    addAction(actionDownFile);
    addAction(actionCreateFolder);
    addAction(actionRenameFolder);

    tp_model = new TreePackageDragDropModel(this);
    setModel(tp_model);
    expandAll();
    setAcceptDrops(true);

    connect(actionUpFile, SIGNAL(triggered(bool)), tp_model, SLOT(moveUpFile()));
    connect(actionDownFile, SIGNAL(triggered(bool)), tp_model, SLOT(moveDownFile()));
    connect(actionCreateFolder, SIGNAL(triggered(bool)), tp_model, SLOT(createFolder()));
    connect(actionRenameFolder, SIGNAL(triggered(bool)), tp_model, SLOT(renameFolder()));
}

TreeView::~TreeView()
{
    delete actionUpFile;
    delete actionDownFile;
    delete actionCreateFolder;
    delete actionRenameFolder;
    delete tp_model;
}

void TreeView::addFile(FileSignatureInfo *fsi)
{
    tp_model->addFileInfo(fsi);
}

void TreeView::contextMenuEvent(QContextMenuEvent *event)
{
    QModelIndex index = indexAt(event->pos());
    if (index.isValid()){
        AbstractFile *af = static_cast<AbstractFile*>(index.internalPointer());

        if (dynamic_cast<RealFile*>(af) && af->getParent()->getName() != "DEBIAN"){
            // you can't rename file in DEBIAN folder
            QMenu menu(this);
            menu.addAction(actionUpFile);
            menu.addAction(actionDownFile);
            menu.exec(event->globalPos());
        } else {
            if (af->isRenamable()){
                QMenu menu(this);
                menu.addAction(actionCreateFolder);
                menu.addAction(actionRenameFolder);
                menu.exec(event->globalPos());
            }
        }
    }
}

