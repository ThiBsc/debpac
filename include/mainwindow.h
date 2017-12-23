#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListView;
class QGridLayout;
class ListViewDragDrop;
class TreeView;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout* gLayout;
    ListViewDragDrop* listView;
    TreeView* treeView;

};

#endif // MAINWINDOW_H
