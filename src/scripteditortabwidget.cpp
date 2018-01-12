#include "scripteditortabwidget.h"
#include "codeeditor.h"
#include "controlfileeditor.h"
#include "syntaxhighlighter.h"
#include <QTextStream>

ScripEditorTabWidget::ScripEditorTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    QFile file("://file/control");
    if (file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        controlFile = new ControlFileEditor(this);
        controlFile->setPlainText(stream.readAll());
        QTabWidget::addTab(controlFile, "control");
    } else {
        controlFile = Q_NULLPTR;
    }
}

ScripEditorTabWidget::~ScripEditorTabWidget()
{
    clear();
    for (CodeEditor *ce : scriptTab){
        delete ce;
    }
    scriptTab.clear();
    if (controlFile)
        delete controlFile;
}

void ScripEditorTabWidget::resetToDefault()
{
    for (CodeEditor *ce : scriptTab){
        int tab = indexOf(ce);
        if (tab != -1){
            removeTab(tab);
            delete ce;
        }
    }
    scriptTab.clear();
}

int ScripEditorTabWidget::addScriptEdit(const QString &label)
{
    int ret = -1;
    int idx = getIndexByName(label);
    if (idx != -1){
        setCurrentIndex(idx);
    } else {
        QFile file("://file/"+label);
        if (file.open(QFile::ReadOnly | QFile::Text)){
            QTextStream stream(&file);
            CodeEditor *ce = new CodeEditor(this);
            ce->setSyntaxHighlighter(new SyntaxHighLighter(SyntaxHighLighter::SCRIPT, ce->document()));
            ce->setPlainText(stream.readAll());
            scriptTab.append(ce);
            ret = QTabWidget::addTab(ce, label);
        }
    }
    return ret;
}

int ScripEditorTabWidget::addScriptEdit(const QIcon &icon, const QString &label)
{
    int ret = addScriptEdit(label);
    if (ret != -1){
        setTabIcon(ret, icon);
    }
    return ret;
}

int ScripEditorTabWidget::addDesktopEdit()
{
    int ret = -1;
    if (controlFile){
        const QString label = controlFile->getPackageName()+".desktop";
        int idx = getIndexByName(label);
        if (idx != -1){
            setCurrentIndex(idx);
        } else {
            QFile file("://file/program.desktop");
            if (file.open(QFile::ReadOnly | QFile::Text)){
                QTextStream stream(&file);
                CodeEditor *ce = new CodeEditor(this);
                ce->setSyntaxHighlighter(new SyntaxHighLighter(SyntaxHighLighter::SECTION_VALUES, ce->document()));
                QString desktop_file = stream.readAll();
                ce->setPlainText(
                            desktop_file.arg(
                                controlFile->getVersion(),
                                controlFile->getPackageName(),
                                "/usr/bin/"+controlFile->getPackageName()
                                )
                            );
                scriptTab.append(ce);
                ret = QTabWidget::addTab(ce, label);
            }
        }
    }
    return ret;
}

int ScripEditorTabWidget::addDesktopEdit(const QIcon &icon)
{
    int ret = addDesktopEdit();
    if (ret != -1){
        setTabIcon(ret, icon);
    }
    return ret;
}

void ScripEditorTabWidget::renameDesktopTab(const QString &oldname, const QString &newname)
{
    int idx = getIndexByName(oldname+".desktop");
    if (idx != -1){
        setTabText(idx, newname+".desktop");
    }
}

int ScripEditorTabWidget::getIndexByName(const QString &name)
{
    int ret = -1;
    for (int i=0; i<count() && ret==-1; i++){
        if (name == tabText(i))
            ret = i;
    }
    return ret;
}

ControlFileEditor *ScripEditorTabWidget::getControlFile()
{
    return controlFile;
}

QVector<CodeEditor *> ScripEditorTabWidget::getScriptTabs()
{
    return scriptTab;
}
