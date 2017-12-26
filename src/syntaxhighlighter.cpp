#include "syntaxhighlighter.h"
#include <QRegularExpressionMatchIterator>

SyntaxHighLighter::SyntaxHighLighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    keysFormat.setForeground(Qt::darkGreen);
    keysFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegularExpression("^\\w+");
    rule.format = keysFormat;
    highlightingRules.append(rule);

    /*valuesFormat.setForeground(Qt::red);
    valuesFormat.setFontWeight(QFont::Normal);
    rule.pattern = QRegularExpression("^\\w+:\\s+(?<value>.*)$");
    rule.format = valuesFormat;
    highlightingRules.append(rule);*/

    singleLineCommentFormat.setForeground(Qt::gray);
    singleLineCommentFormat.setFontWeight(QFont::Normal);
    rule.pattern = QRegularExpression("^#.*$");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);
}

SyntaxHighLighter::~SyntaxHighLighter()
{
    highlightingRules.clear();
}

void SyntaxHighLighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
