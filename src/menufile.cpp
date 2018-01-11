#include "menufile.h"

MenuFile::MenuFile(QWidget *parent)
    : QMenu(parent)
{
    init();
}

MenuFile::MenuFile(const QString &title, QWidget *parent)
    : QMenu(title, parent)
{
    init();
}

MenuFile::~MenuFile()
{
    clear();
}

QMenu *MenuFile::getMenuScript()
{
    return menuScript;
}

void MenuFile::actionScriptTriggered()
{
    QObject *action = QObject::sender();
    if (action == actionPostinst)
        emit wantScript("postinst");
    else if (action == actionPreinst)
        emit wantScript("preinst");
    else if (action == actionPostrm)
        emit wantScript("postrm");
    else if (action == actionPrerm)
        emit wantScript("prerm");
}

void MenuFile::actionDesktopTriggered()
{
    emit wantDesktop("program.desktop");
}

void MenuFile::actionSavePackageProjectTriggered()
{
    emit savePackageProject();
}

void MenuFile::actionImportPackageProjectTriggered()
{
    emit importPackageProject();
}

void MenuFile::actionGeneratePackageTriggered()
{
    emit wantGeneratePackage();
}

void MenuFile::init()
{
    setTitle("File");
    menuScript = addMenu(QIcon("://icon/add_script.png"), "Add script");
    actionPostinst = menuScript->addAction("postinst");
    actionPreinst = menuScript->addAction("preinst");;
    actionPostrm = menuScript->addAction("postrm");;
    actionPrerm = menuScript->addAction("prerm");;

    actionDesktop = addAction(QIcon("://icon/desktop.png"), "Add .desktop file");
    actionGeneratePackage = addAction(QIcon("://icon/generate.png"), "Generate package");
    addSeparator();
    actionSavePackageProject = addAction(QIcon("://icon/diskette.png"), "Save config");
    actionImportPackageProject = addAction(QIcon("://icon/import.png"), "Import config");

    connect(actionPostinst, SIGNAL(triggered(bool)), this, SLOT(actionScriptTriggered()));
    connect(actionPreinst, SIGNAL(triggered(bool)), this, SLOT(actionScriptTriggered()));
    connect(actionPostrm, SIGNAL(triggered(bool)), this, SLOT(actionScriptTriggered()));
    connect(actionPrerm, SIGNAL(triggered(bool)), this, SLOT(actionScriptTriggered()));
    connect(actionDesktop, SIGNAL(triggered(bool)), this, SLOT(actionDesktopTriggered()));

    connect(actionGeneratePackage, SIGNAL(triggered(bool)), this, SLOT(actionGeneratePackageTriggered()));
    connect(actionSavePackageProject, SIGNAL(triggered(bool)), this, SLOT(actionSavePackageProjectTriggered()));
    connect(actionImportPackageProject, SIGNAL(triggered(bool)), this, SLOT(actionImportPackageProjectTriggered()));
}
