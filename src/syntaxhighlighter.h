#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QVector>
#include <QRegularExpression>

/**
 * @brief The SyntaxHighLighter class
 * To perform a Syntaxic coloration when editing files
 */

class SyntaxHighLighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    enum SyntaxType { KEY_VALUE=0, SECTION_VALUES, SCRIPT };

    SyntaxHighLighter(SyntaxType syntax, QTextDocument *parent = 0);
    ~SyntaxHighLighter();

protected:
    virtual void highlightBlock(const QString &text);

private:
    void initSyntaxKeyValue();
    void initSyntaxSectionValues();
    void initSyntaxScript();
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

};

#endif // SYNTAXHIGHLIGHTER_H
