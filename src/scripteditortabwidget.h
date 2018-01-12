#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QVector>

class QPlainTextEdit;
class CodeEditor;
class ControlFileEditor;

/**
 * @brief The ScripEditorTabWidget class
 * The TabWidget for the debian files edition:
 * post/pre-inst/rm, .desktop and control file
 */

class ScripEditorTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    ScripEditorTabWidget(QWidget *parent = Q_NULLPTR);
    ~ScripEditorTabWidget();
    void resetToDefault();
    ControlFileEditor *getControlFile();
    QVector<CodeEditor *> getScriptTabs();
    int getIndexByName(const QString& name);

public slots:
    int addScriptEdit(const QString &label);
    int addScriptEdit(const QIcon &icon, const QString &label);
    int addDesktopEdit();
    int addDesktopEdit(const QIcon &icon);
    void renameDesktopTab(const QString &oldname, const QString &newname);

private:
    ControlFileEditor *controlFile;
    QVector<CodeEditor*> scriptTab;

};

#endif // TABWIDGET_H
