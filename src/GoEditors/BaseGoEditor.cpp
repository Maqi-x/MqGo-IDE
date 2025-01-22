// ------------------------ Qt ----------------- //
#include <QDebug>
#include <QKeyEvent>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTextCursor>
#include <QtGui/QTextBlock>
#include <iostream>
// --------------------------------------------- //

#include <Editors/Go/BaseGoEditor.hpp>

using std::cout;

BaseGoEditor::BaseGoEditor(QWidget *parent) : QPlainTextEdit(parent) {}

void BaseGoEditor::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Tab) {
        textCursor().insertText("    ");
    } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QTextCursor cur = textCursor();
        cur.beginEditBlock();

        cur.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 1);
        QString nextChar = cur.selectedText();
        cur.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 2);
        QString prevChar = cur.selectedText();

        //		auto x =
        //        (prevChar == "{" && nextChar == "}") ||
        //        (prevChar == "[" && nextChar == "]") ||
        //        (prevChar == "(" && nextChar == ")");

        auto x = (prevChar == "{" && nextChar == "}");
        auto y = (prevChar == "[" && nextChar == "]");
        auto z = (prevChar == "(" && nextChar == ")");

        auto xyz = x || y || z;

        cur.movePosition(QTextCursor::StartOfBlock, QTextCursor::KeepAnchor);
        QString currentLine = cur.selectedText();

        QRegularExpression indentRegex(R"(^\s+)");
        QRegularExpressionMatch match = indentRegex.match(currentLine);
        QString indentation = match.hasMatch() ? match.captured(0) : "";

        cur.movePosition(QTextCursor::EndOfBlock, QTextCursor::KeepAnchor);
        QString textAfterCursor = cur.selectedText();

        cur.removeSelectedText();

        cur.insertText("\n" + indentation /*+ textAfterCursor*/);

        if (xyz) {
            cur.insertText("    \n" + indentation);
            if (x) {
                cur.insertText("}");
            } else if (y) {
                cur.insertText("]");
            } else if (z) {
                cur.insertText(")");
            }
            textAfterCursor.remove(0, 1);
        }

        cur.insertText(textAfterCursor);

        cur.movePosition(QTextCursor::StartOfBlock);
        cur.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, indentation.length());

        if (xyz) {
            cur.movePosition(QTextCursor::Up, QTextCursor::MoveAnchor, 1);
            cur.movePosition(QTextCursor::EndOfBlock, QTextCursor::MoveAnchor);
            setTextCursor(cur);
        }

        if (!xyz) {
            cur.movePosition(QTextCursor::StartOfBlock);

            QString lineText = cur.block().text();
            QRegularExpressionMatch match = indentRegex.match(lineText);

            if (match.hasMatch()) {
                int indentLength = match.captured(0).length();
                cur.movePosition(QTextCursor::NextCharacter, QTextCursor::MoveAnchor, indentLength);
            }
            setTextCursor(cur);
        }

        cur.endEditBlock();
    } else if ((event->key() == Qt::Key_ParenRight || event->key() == Qt::Key_BracketRight ||
                event->key() == Qt::Key_BraceRight || event->key() == Qt::Key_QuoteDbl ||
                event->key() == Qt::Key_Apostrophe || event->key() == Qt::Key_QuoteLeft) &&
               textCursor().position() < toPlainText().length() &&
               toPlainText().at(textCursor().position()) == event->text()) {
        QTextCursor cur = textCursor();
        cur.movePosition(QTextCursor::Right);
        setTextCursor(cur);
    } else if (event->key() == Qt::Key_ParenLeft || event->key() == Qt::Key_BracketLeft ||
               event->key() == Qt::Key_BraceLeft || event->key() == Qt::Key_QuoteDbl ||
               event->key() == Qt::Key_Apostrophe || event->key() == Qt::Key_QuoteLeft) {
        QChar openChar = event->text().at(0);
        QChar closeChar;

        if (openChar == '(')
            closeChar = ')';
        else if (openChar == '[')
            closeChar = ']';
        else if (openChar == '{')
            closeChar = '}';
        else if (openChar == '"')
            closeChar = '"';
        else if (openChar == '\'')
            closeChar = '\'';
        else if (openChar == '`')
            closeChar = '`';

        QTextCursor cur = textCursor();
        cur.insertText(QString(openChar) + QString(closeChar));
        cur.movePosition(QTextCursor::Left);
        setTextCursor(cur);
    } else {
        QPlainTextEdit::keyPressEvent(event);
    }
}
