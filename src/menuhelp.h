#ifndef MENUHELP_H
#define MENUHELP_H

#include <QMenu>

class MenuHelp : public QMenu
{
public:
    MenuHelp(QWidget *parent = Q_NULLPTR);
    MenuHelp(const QString &title, QWidget *parent = Q_NULLPTR);
    ~MenuHelp();

private:
    void init();
    QAction *actionAbout;
    QAction *actionCredits;

};

#endif // MENUHELP_H
