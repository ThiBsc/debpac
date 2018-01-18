#include "treeview.h"
#include "treepackagedragdropmodel.h"
#include "filesignatureinfo.hpp"
#include "realfile.h"
#include <QMenu>
#include <QContextMenuEvent>

TreeView::TreeView(QWidget *parent)
    : QTreeView(parent)
{
    upFile = new QAction("Up file", this);
    downFile = new QAction("Down file", this);
    createFolder = new QAction("Create folder", this);
    renameFolder = new QAction("Rename folder", this);

    upFile->setShortcut(QKeySequence(Qt::CTRL, Qt::SHIFT, Qt::Key_Up));
    downFile->setShortcut(QKeySequence(Qt::CTRL, Qt::SHIFT, Qt::Key_Down));
    createFolder->setShortcut(QKeySequence(Qt::CTRL, Qt::SHIFT, Qt::Key_N));
    renameFolder->setShortcut(QKeySequence(Qt::CTRL, Qt::SHIFT, Qt::Key_R));

    tp_model = new TreePackageDragDropModel(this);
    setModel(tp_model);
    expandAll();
    setAcceptDrops(true);
}

TreeView::~TreeView()
{
    delete upFile;
    delete downFile;
    delete createFolder;
    delete renameFolder;
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

        if (dynamic_cast<RealFile*>(af)){
            QMenu menu(this);
            menu.addAction(upFile);
            menu.addAction(downFile);
            menu.exec(event->globalPos());
        } else {
            if (af->isRenamable()){
                QMenu menu(this);
                menu.addAction(createFolder);
                menu.addAction(renameFolder);
                menu.exec(event->globalPos());
            }
        }
    }
}

