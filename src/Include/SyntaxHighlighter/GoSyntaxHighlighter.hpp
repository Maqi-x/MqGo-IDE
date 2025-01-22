#pragma once
#ifndef SYNTAXHIGHLIGHTER_HPP
#define SYNTAXHIGHLIGHTER_HPP

// --------------- Qt --------------- //
#include <QBrush>
#include <QColor>
#include <QList>
#include <QPair>
#include <QRegularExpression>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextDocument>
// --------------------------------- //

#include <constants.hpp>

class GoSyntaxHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

  public:
    explicit GoSyntaxHighlighter(QTextDocument *parent);

  signals:
    void highlightStarted();

  protected:
    void highlightBlock(const QString &text) override;

    // private:
    //     bool isInString(int index, const QList<QPair<int, int>>
    //     &stringRanges);
};

#endif