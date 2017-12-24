#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QVector>
#include <QRegularExpression>

class SyntaxHighLighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHighLighter(QTextDocument *parent = 0);
    ~SyntaxHighLighter();

protected:
    virtual void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keysFormat;
    // QTextCharFormat valuesFormat;
    QTextCharFormat singleLineCommentFormat;

};

#endif // SYNTAXHIGHLIGHTER_H
