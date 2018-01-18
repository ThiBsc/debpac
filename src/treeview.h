#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>

class TreePackageDragDropModel;
class FileSignatureInfo;

/**
 * @brief The TreeView class
 * The TreeView that show a preview of the Debian package content
 */

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget *parent = Q_NULLPTR);
    ~TreeView();

public slots:
    void addFile(FileSignatureInfo *fsi);

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

private:
    TreePackageDragDropModel *tp_model;
    QAction *upFile;
    QAction *downFile;
    QAction *createFolder;
    QAction *renameFolder;

};

#endif // TREEVIEW_H
