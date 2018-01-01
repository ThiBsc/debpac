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

private slots:
    void actionScriptTriggered();
    void actionDesktopTriggered();

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

};

#endif // FILEMENU_H
