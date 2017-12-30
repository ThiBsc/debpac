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

public slots:
    void infoIsEdited();

signals:
    void packageNameChanged(const QString &pname);
    void versionChanged(const QString &version);

private:
    SyntaxHighLighter *highlighter;

};

#endif // CONTROLFILEEDITOR_H
