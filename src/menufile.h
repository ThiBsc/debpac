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

private slots:
    void actionScriptTriggered();

private:
    void init();
    QMenu *menuScript;
    QAction *actionPostinst;
    QAction *actionPreinst;
    QAction *actionPostrm;
    QAction *actionPrerm;

    QAction *actionGeneratePackage;
    QAction *actionSavePackageProject;

};

#endif // FILEMENU_H
