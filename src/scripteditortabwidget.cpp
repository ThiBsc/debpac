#include "scripteditortabwidget.h"
#include "codeeditor.h"
#include "controlfileeditor.h"
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
    if (controlFile)
        delete controlFile;
}

int ScripEditorTabWidget::addScriptEdit(const QString &label)
{
    int ret = -1;
    QFile file("://file/"+label);
    if (file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        CodeEditor *ce = new CodeEditor(this);
        ce->setPlainText(stream.readAll());
        scriptTab.append(ce);
        ret = QTabWidget::addTab(ce, label);
    }
    return ret;
}

int ScripEditorTabWidget::addScriptEdit(const QIcon &icon, const QString &label)
{
    int ret = -1;
    QFile file("://file/"+label);
    if (file.open(QFile::ReadOnly | QFile::Text)){
        QTextStream stream(&file);
        CodeEditor *ce = new CodeEditor(this);
        ce->setPlainText(stream.readAll());
        scriptTab.append(ce);
        ret = QTabWidget::addTab(ce, icon, label);
    }
    return ret;
}

ControlFileEditor *ScripEditorTabWidget::getControlFile()
{
    return controlFile;
}
