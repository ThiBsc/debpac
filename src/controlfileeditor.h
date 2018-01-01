#ifndef CONTROLFILEEDITOR_H
#define CONTROLFILEEDITOR_H

#include "codeeditor.h"

class SyntaxHighLighter;

class ControlFileEditor : public CodeEditor
{
    Q_OBJECT
public:
    ControlFileEditor(QWidget *parent = Q_NULLPTR);
    ~ControlFileEditor();
    QString getPackageName() const;
    QString getVersion() const;

public slots:
    void infoIsEdited();

signals:
    void packageNameChanged(const QString &pname);
    void versionChanged(const QString &version);

private:
    QString packageName;
    QString version;
    SyntaxHighLighter *highlighter;

};

#endif // CONTROLFILEEDITOR_H
