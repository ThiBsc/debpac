#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListView;
class QGridLayout;
class QSplitter;
class ScripEditorTabWidget;
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
    QSplitter *splitter;
    ScripEditorTabWidget *tabWidget;
    TreeView* treeView;

};

#endif // MAINWINDOW_H
