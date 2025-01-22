#ifndef __cplusplus
#error MqGo! requires a C++ compiler preferably in the c++17 standard or higher
#endif

// --------------- Qt --------------- //
#include <QApplication>
#include <QBrush>
#include <QColor>
#include <QDebug>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QRegularExpression>
#include <QSettings>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QTextCursor>
// --------------------------------- //

#include <Editors/Go/BaseGoEditor.hpp>
#include <QssLoader.hpp>
#include <SyntaxHighlighter/GoSyntaxHighlighter.hpp>
#include <Utils/ColorPicker.hpp>
#include <constants.hpp>
#include <stdio.h>

QString getStyle(const QString &name = "style.qss") {
    QFile file(":/" + name);
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream stream(&file);
        QString content = stream.readAll();
        file.close();
        return content;
    }
    return (QString) "";
}

int main(int argc, char *argv[]) {
    QSettings settings(QSettings::UserScope, "MqApps", "MqGo!");

    QApplication app(argc, argv);
    QMainWindow w;

    w.setWindowTitle("MqGo!");
    w.resize(settings.value("Window/size", QSize(700, 500)).toSize());

    auto *editor = new BaseGoEditor();

    editor->setStyleSheet(getStyle());

    new GoSyntaxHighlighter(editor->document());
    w.setCentralWidget(editor);
    w.show();

    auto code = app.exec();
    settings.setValue("Window/size", w.size());
    return code;
}
