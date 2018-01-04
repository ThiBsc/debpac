#include "menuhelp.h"
#include "mainwindow.h"
#include <QMessageBox>

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

void MenuHelp::showAbout()
{
    QMessageBox::about(parentWidget(), tr("About"), "<div><b>debpac v"+MainWindow::version+"</b><br>by thibDev, <a href='https://github.com/thibDev/debpac'>GitHub</a></div>");
}

void MenuHelp::showCredits()
{
    const QString credit = "<div><b>Icons from <a href='www.flaticon.com'>flaticon</a></b><div style='text-align:center;'>"
                           "<p><img src='://icon/binary.png' alt='binary' height='24' width='24'/>, <img src='://icon/file.png' alt='file' height='24' width='24'/>, "
                           "<img src='://icon/diskette.png' alt='diskette' height='24' width='24'/>, <img src='://icon/generate.png' alt='generate' height='24' width='24'/>, "
                           "<img src='://icon/add_script.png' alt='add_script' height='24' width='24'/>, <img src='://icon/about.png' alt='about' height='24' width='24'/>, "
                           "<img src='://icon/credits.png' alt='credits' height='24' width='24'/> - <img src='://icon/import.png' alt='import' height='24' width='24'/><br>"
                           "Icon made by <a href='https://www.flaticon.com/authors/freepik'>Freepik</a></p>"
                           "<p><img src='://icon/audio.png' alt='audio' height='24' width='24'/>, <img src='://icon/package.png' alt='package' height='24' width='24'/>, "
                           "<img src='://icon/image.png' alt='image' height='24' width='24'/><br>"
                           "Icon made by <a href='https://www.flaticon.com/authors/pixel-buddha'>Pixel Buddha</a></p>"
                           "<p><img src='://icon/archive.png' alt='archive' height='24' width='24'/><br>"
                           "Icon made by <a href='https://www.flaticon.com/authors/roundicons'>Roundicons</a></p>"
                           "<p><img src='://icon/folder.png' alt='folder' height='24' width='24'/><br>"
                           "Icon made by <a href='https://www.flaticon.com/authors/smashicons'>Smashicons</a></p>"
                           "<p><img src='://icon/desktop.png' alt='desktop' height='24' width='24'/><br>"
                           "Icon made by <a href='https://www.flaticon.com/authors/vectors-market'>vectors Market</a></p>"
                           "</div></div>";
    QMessageBox::information(parentWidget(), tr("Credits"), credit);
}

void MenuHelp::init()
{
    setTitle("?");
    actionAbout = addAction(QIcon("://icon/about.png"), "About");
    actionCredits = addAction(QIcon("://icon/credits.png"), "Credits");

    connect(actionAbout, SIGNAL(triggered(bool)), this, SLOT(showAbout()));
    connect(actionCredits, SIGNAL(triggered(bool)), this, SLOT(showCredits()));
}
