#ifndef MENUHELP_H
#define MENUHELP_H

#include <QMenu>

/**
 * @brief The MenuHelp class
 * The menu that contains info about debpac
 */

class MenuHelp : public QMenu
{
    Q_OBJECT

public:
    MenuHelp(QWidget *parent = Q_NULLPTR);
    MenuHelp(const QString &title, QWidget *parent = Q_NULLPTR);
    ~MenuHelp();

private slots:
    void showAbout();
    void showCredits();

private:
    void init();
    QAction *actionAbout;
    QAction *actionCredits;

};

#endif // MENUHELP_H
