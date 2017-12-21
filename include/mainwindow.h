#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QListView;
class QGridLayout;
class ListFileModel;

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
    QListView* listFileView;
    ListFileModel* listModel;
};

#endif // MAINWINDOW_H
