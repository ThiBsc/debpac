#include "controlfileeditor.h"
#include "syntaxhighlighter.h"
#include <QTextBlock>
#include <QRegularExpression>

ControlFileEditor::ControlFileEditor(QWidget *parent)
    : CodeEditor(parent)
{
    connect(this, SIGNAL(textChanged()), this, SLOT(infoIsEdited()));
    showLineNumber(false);
    showHighlightLine(false);

    highlighter = new SyntaxHighLighter(document());
}

ControlFileEditor::~ControlFileEditor()
{    
    delete highlighter;
}

void ControlFileEditor::infoIsEdited()
{
    QTextBlock txtBlock = document()->findBlockByNumber(textCursor().blockNumber());
    QString curLine = txtBlock.text();
    QRegularExpression regex("^(?<info>Package|Version):(?<value>.*)$");
    QRegularExpressionMatch rem = regex.match(curLine);
    if (rem.hasMatch()){
        if ("Package" == rem.captured("info")){
            emit packageNameChanged(rem.captured("value"));
        } else {
            emit versionChanged(rem.captured("value"));
        }
    }
}
