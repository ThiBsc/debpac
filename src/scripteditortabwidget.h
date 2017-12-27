#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QList>

class QPlainTextEdit;
class CodeEditor;
class ControlFileEditor;

class ScripEditorTabWidget : public QTabWidget
{
public:
    ScripEditorTabWidget(QWidget *parent = Q_NULLPTR);
    ~ScripEditorTabWidget();
    int addScriptEdit(const QString &label);
    int addScriptEdit(const QIcon &icon, const QString &label);
    ControlFileEditor *getControlFile();

private:
    ControlFileEditor *controlFile;
    QList<CodeEditor*> scriptTab;

};

#endif // TABWIDGET_H
