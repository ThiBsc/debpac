#include "../include/tabwidget.h"
#include "../include/syntaxhighlighter.h"
#include <QPlainTextEdit>
#include <QTextStream>

TabWidget::TabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    addScriptEdit("control");
}

TabWidget::~TabWidget()
{
    clear();

    for (SyntaxHighLighter *shl : highlighters){
        delete shl;
    }
    for (QPlainTextEdit *pte : scriptTab){
        delete pte;
    }
}

int TabWidget::addScriptEdit(const QString &label)
{
    int ret = -1;
    QFile file("://file/"+label);
    if (file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        QPlainTextEdit *pte = new QPlainTextEdit(this);
        pte->setPlainText(stream.readAll());
        scriptTab.append(pte);
        SyntaxHighLighter *shl = new SyntaxHighLighter(pte->document());
        highlighters.append(shl);
        ret = QTabWidget::addTab(pte, label);
    }
    return ret;
}

int TabWidget::addScriptEdit(const QIcon &icon, const QString &label)
{
    int ret = -1;
    QFile file("://file/"+label);
    if (file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        QPlainTextEdit *pte = new QPlainTextEdit(this);
        pte->setPlainText(stream.readAll());
        scriptTab.append(pte);
        SyntaxHighLighter *shl = new SyntaxHighLighter(pte->document());
        highlighters.append(shl);
        ret = QTabWidget::addTab(pte, icon, label);
    }
    return ret;
}
