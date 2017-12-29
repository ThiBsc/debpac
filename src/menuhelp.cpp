#include "menuhelp.h"

MenuHelp::MenuHelp(QWidget *parent)
    : QMenu(parent)
{
    init();
}

MenuHelp::MenuHelp(const QString &title, QWidget *parent)
    : QMenu(title, parent)
{
    init();
}

MenuHelp::~MenuHelp()
{
    clear();
}

void MenuHelp::init()
{
    setTitle("?");
    actionAbout = addAction(QIcon("://icon/about.png"), "About");
    actionCredits = addAction(QIcon("://icon/credits.png"), "Credits");
}
