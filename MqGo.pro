QT += core gui widgets

TARGET = MqGo!
TEMPLATE = app

SOURCES += src/main.cpp \
           src/SyntaxHighlighters/GoSyntaxHighlighter.cpp \
           src/GoEditors/BaseGoEditor.cpp \
           src/ColorPicker.cpp

HEADERS += src/Include/SyntaxHighlighter/GoSyntaxHighlighter.hpp
HEADERS += src/Include/Editors/Go/BaseGoEditor.hpp
HEADERS += src/Include/Utils/ColorPicker.hpp

DESTDIR = bin/
OBJECTS_DIR = build/
MOC_DIR = build/
RCC_DIR = build/
UI_DIR = build/
INCLUDEPATH += $$PWD/src/Include

CONFIG += moc
RESOURCES += assets/init.qrc
CONFIG += console
CONFIG += precompile_header