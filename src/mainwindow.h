#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListView;
class QGridLayout;
class QSplitter;
class ScripEditorTabWidget;
class TreeView;
class MenuFile;
class MenuHelp;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static const QString version;

public slots:
    void saveToJson();
    void restoreFromJson();
    void generatePackage();

private:
    Ui::MainWindow *ui;
    MenuFile *menuFile;
    MenuHelp *menuHelp;

    QGridLayout *gLayout;
    QSplitter *splitter;
    ScripEditorTabWidget *tabWidget;
    TreeView *treeView;

};

#endif // MAINWINDOW_H
