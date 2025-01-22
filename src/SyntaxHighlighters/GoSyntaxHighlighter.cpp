#include <SyntaxHighlighter/GoSyntaxHighlighter.hpp>
#include <Utils/ColorPicker.hpp>
#include <constants.hpp>

GoSyntaxHighlighter::GoSyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {}

void GoSyntaxHighlighter::highlightBlock(const QString &text) {
    // -------------------- Keywoards --------------------- //
    QMap<QStringList, QTextCharFormat> keywordFormats;

    QTextCharFormat SpecialKeywordsFormat;
    SpecialKeywordsFormat.setForeground(clr::yellow);
    keywordFormats.insert({"package", "import", "defer", "return", "range", "nil"}, SpecialKeywordsFormat);

    QTextCharFormat ConditionalInstructionsFormat;
    ConditionalInstructionsFormat.setForeground(clr::orange);
    keywordFormats.insert({"if", "else", "switch", "case"}, ConditionalInstructionsFormat);

    QTextCharFormat LoopsKeywoardsFormat;
    LoopsKeywoardsFormat.setForeground(clr::orangeRed);
    keywordFormats.insert({"for", "break", "continue"}, LoopsKeywoardsFormat);

    QTextCharFormat DeclarationInstructions;
    DeclarationInstructions.setForeground(clr::magenta);
    keywordFormats.insert({"var", "func", "const", "type"}, DeclarationInstructions);

    QTextCharFormat PremitiveTypesFormat;
    PremitiveTypesFormat.setForeground(clr::brown);
    keywordFormats.insert({"string", "int", "int8", "int16", "int32", "int64", "float", "float64", "float32",
                           "rune", "uintptr", "uint", "uint8", "uint16", "uint32", "uint64"},
                          PremitiveTypesFormat);

    keywordFormats.insert({"true"}, []() {
        QTextCharFormat fmt;
        fmt.setForeground(clr::lightGreen);
        return fmt;
    }());

    keywordFormats.insert({"false"}, []() {
        QTextCharFormat fmt;
        fmt.setForeground(clr::tomato);
        return fmt;
    }());

    for (auto it = keywordFormats.begin(); it != keywordFormats.end(); it++) {
        const QStringList &keywords = it.key();
        const QTextCharFormat &format = it.value();

        for (const QString &keyword : keywords) {
            QRegularExpression keywordRegex("\\b" + QRegularExpression::escape(keyword) + "\\b");
            QRegularExpressionMatchIterator keywordMatches = keywordRegex.globalMatch(text);

            while (keywordMatches.hasNext()) {
                QRegularExpressionMatch match = keywordMatches.next();
                setFormat(match.capturedStart(), match.capturedLength(), format);
            }
        }
    }

    // -------------------------- function cales -------------------------- //
    QTextCharFormat functionFormat;
    functionFormat.setForeground(clr::steelBlue);

    // xyz( ... )
    QRegularExpression functionRegex("\\b\\w+\\(");
    QRegularExpressionMatchIterator functionMatches = functionRegex.globalMatch(text);

    while (functionMatches.hasNext()) {
        QRegularExpressionMatch match = functionMatches.next();
        setFormat(match.capturedStart(), match.capturedLength() - 1, functionFormat);
    }

    // ------------------ functions/methods declarations ----------------- //
    QTextCharFormat funcKeywordFormat;
    funcKeywordFormat.setForeground(clr::orange);

    QTextCharFormat funcNameFormat;
    funcNameFormat.setForeground(clr::aqua);

    QTextCharFormat methodReceiverNameFormat;
    methodReceiverNameFormat.setForeground(clr::aqua);

    QTextCharFormat methodReceiverTypeFormat;
    methodReceiverTypeFormat.setForeground(clr::skyBlue);

    QRegularExpressionMatchIterator funcDeclarationMatches =
        QRegularExpression("\\bfunc\\s+(\\w+)\\s*\\(").globalMatch(text);

    while (funcDeclarationMatches.hasNext()) {
        QRegularExpressionMatch match = funcDeclarationMatches.next();

        setFormat(match.capturedStart(1), match.capturedLength(1), funcNameFormat);
    }

    QRegularExpression methodDeclarationRegex("\\bfunc\\s*\\(\\s*(\\w+)\\s+(\\w+)\\s*\\)\\s*(\\w+)\\s*\\(");
    QRegularExpressionMatchIterator methodDeclarationMatches = methodDeclarationRegex.globalMatch(text);

    while (methodDeclarationMatches.hasNext()) {
        QRegularExpressionMatch match = methodDeclarationMatches.next();

        setFormat(match.capturedStart(1), match.capturedLength(1), methodReceiverNameFormat);

        setFormat(match.capturedStart(2), match.capturedLength(2), methodReceiverTypeFormat);

        setFormat(match.capturedStart(3), match.capturedLength(3), funcNameFormat);
    }

    // ----------------------- objects references --------------------- //
    QTextCharFormat objectReferenceFormat;
    objectReferenceFormat.setForeground(clr::powderBlue);

    // xyz.xyz
    QRegularExpression objectReferenceRegex("\\b(\\w+)\\.");
    QRegularExpressionMatchIterator objectReferenceMatches = objectReferenceRegex.globalMatch(text);

    while (objectReferenceMatches.hasNext()) {
        QRegularExpressionMatch match = objectReferenceMatches.next();
        setFormat(match.capturedStart(1), match.capturedLength(1), objectReferenceFormat);
    }

    // ------------------------ Numbers ------------------------- //
    QTextCharFormat numberFormat;
    numberFormat.setForeground(clr::lightGreen);

    QRegularExpression numberRegex("\\b\\d+(\\.\\d+)?\\b");
    QRegularExpressionMatchIterator numberMatches = numberRegex.globalMatch(text);

    while (numberMatches.hasNext()) {
        QRegularExpressionMatch match = numberMatches.next();
        setFormat(match.capturedStart(), match.capturedLength(), numberFormat);
    }

    // ------------------------ Strings ---------------------------- //
    QTextCharFormat stringFormat;
    stringFormat.setForeground(clr::green);

    QTextCharFormat escapeFormat;
    escapeFormat.setForeground(clr::orange);

    QRegularExpression stringRegex("\"([^\"\\\\]|\\\\.)*\"");
    QRegularExpressionMatchIterator stringMatches = stringRegex.globalMatch(text);

    while (stringMatches.hasNext()) {
        QRegularExpressionMatch match = stringMatches.next();
        setFormat(match.capturedStart(), match.capturedLength(), stringFormat);

        QRegularExpression escapeRegex("\\\\[abfnrtv\\\\'\"?]|\\\\x[0-9A-Fa-f]{2}|\\\\[0-7]{1,3}|\\\\u[0-"
                                       "9A-Fa-f]{4}|\\\\U[0-9A-Fa-f]{8}");
        QRegularExpressionMatchIterator escapeMatches = escapeRegex.globalMatch(match.captured());

        while (escapeMatches.hasNext()) {
            QRegularExpressionMatch escapeMatch = escapeMatches.next();
            setFormat(match.capturedStart() + escapeMatch.capturedStart(), escapeMatch.capturedLength(),
                      escapeFormat);
        }
    }

    // ----------------------- runes ------------------------ //
    QTextCharFormat runFormat;
    runFormat.setForeground(clr::green);

    // 'x' / '\xyz'
    QRegularExpression runeRegex("'([^'\\\\]|\\\\.)'");
    QRegularExpressionMatchIterator runMatches = runeRegex.globalMatch(text);

    while (runMatches.hasNext()) {
        QRegularExpressionMatch match = runMatches.next();
        setFormat(match.capturedStart(), match.capturedLength(), runFormat);

        // \xyz
        QRegularExpression escapeRegex("\\\\[abfnrtv\\\\'\"?]|\\\\x[0-9A-Fa-f]{2}|\\\\[0-7]{1,3}|\\\\u[0-"
                                       "9A-Fa-f]{4}|\\\\U[0-9A-Fa-f]{8}");
        QRegularExpressionMatchIterator escapeMatches = escapeRegex.globalMatch(match.captured());

        while (escapeMatches.hasNext()) {
            QRegularExpressionMatch escapeMatch = escapeMatches.next();
            setFormat(match.capturedStart() + escapeMatch.capturedStart(), escapeMatch.capturedLength(),
                      escapeFormat);
        }
    }
}
