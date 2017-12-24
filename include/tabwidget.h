#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QList>

class QPlainTextEdit;
class SyntaxHighLighter;

class TabWidget : public QTabWidget
{
public:
    TabWidget(QWidget *parent = Q_NULLPTR);
    ~TabWidget();
    int addScriptEdit(const QString &label);
    int addScriptEdit(const QIcon &icon, const QString &label);

private:
    QList<QPlainTextEdit*> scriptTab;
    QList<SyntaxHighLighter*> highlighters;

};

#endif // TABWIDGET_H
