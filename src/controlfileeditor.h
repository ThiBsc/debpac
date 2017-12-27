#ifndef CONTROLFILEEDITOR_H
#define CONTROLFILEEDITOR_H

#include "codeeditor.h"

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
};

#endif // CONTROLFILEEDITOR_H
