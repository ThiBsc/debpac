#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QList>

class QPlainTextEdit;
class CodeEditor;
class ControlFileEditor;

class ScripEditorTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    ScripEditorTabWidget(QWidget *parent = Q_NULLPTR);
    ~ScripEditorTabWidget();
    ControlFileEditor *getControlFile();
    QList<CodeEditor *> getScriptTabs();

public slots:
    int addScriptEdit(const QString &label);
    int addScriptEdit(const QIcon &icon, const QString &label);
    int addDesktopEdit();
    int addDesktopEdit(const QIcon &icon);
    void renameDesktopTab(const QString &oldname, const QString &newname);

private:
    int getIndexByName(const QString& name);
    ControlFileEditor *controlFile;
    QList<CodeEditor*> scriptTab;

};

#endif // TABWIDGET_H
