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

void MenuFile::init()
{
    setTitle("File");
    menuScript = addMenu(QIcon("://icon/add_script.png"), "Add script");
    actionPostinst = menuScript->addAction("postinst");
    actionPreinst = menuScript->addAction("preinst");;
    actionPostrm = menuScript->addAction("postrm");;
    actionPrerm = menuScript->addAction("prerm");;

    actionGeneratePackage = addAction(QIcon("://icon/generate.png"), "Generate package");
    addSeparator();
    actionSavePackageProject = addAction(QIcon("://icon/diskette.png"), "Save config");
}
