#ifndef FILEMENU_H
#define FILEMENU_H

#include <QMenu>

class MenuFile : public QMenu
{
    Q_OBJECT
public:
    MenuFile(QWidget *parent = Q_NULLPTR);
    MenuFile(const QString &title, QWidget *parent = Q_NULLPTR);
    ~MenuFile();

signals:
    void wantScript(const QString&);
    void wantDesktop(const QString&);
    void savePackageProject();
    void importPackageProject();
    void wantGeneratePackage();

private slots:
    void actionScriptTriggered();
    void actionDesktopTriggered();
    void actionSavePackageProjectTriggered();
    void actionImportPackageProjectTriggered();
    void actionGeneratePackageTriggered();

private:
    void init();
    QMenu *menuScript;
    QAction *actionPostinst;
    QAction *actionPreinst;
    QAction *actionPostrm;
    QAction *actionPrerm;

    QAction *actionDesktop;
    QAction *actionGeneratePackage;
    QAction *actionSavePackageProject;
    QAction *actionImportPackageProject;

};

#endif // FILEMENU_H
