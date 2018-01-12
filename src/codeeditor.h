#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>

class QSyntaxHighlighter;

/**
 * @brief The CodeEditor class
 * http://doc.qt.io/qt-5/qtwidgets-widgets-codeeditor-example.html
 */

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = Q_NULLPTR);
    ~CodeEditor();
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void showLineNumber(bool print);
    void showHighlightLine(bool hl);
    void setSyntaxHighlighter(QSyntaxHighlighter *highlighter);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);

private:    
    QSyntaxHighlighter *highlighter;
    QWidget *lineNumberArea;
    bool activeHighlight;

};

#endif // CODEEDITOR_H
