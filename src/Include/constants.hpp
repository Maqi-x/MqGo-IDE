#pragma once

#include <QBrush>
#include <QColor>
#include <Utils/Types.hpp>
#include <string>

namespace clr {
const QBrush green = QBrush(QColor(0, 128, 0));
const QBrush red = QBrush(QColor(255, 0, 0));
const QBrush brightRed = QBrush(QColor(255, 0, 0));
const QBrush orangeRed = QBrush(QColor(255, 69, 0));
const QBrush tomato = QBrush(QColor(255, 99, 71));
const QBrush lightSalmon = QBrush(QColor(255, 160, 122));
const QBrush lightPink = QBrush(QColor(255, 182, 193));
const QBrush crimson = QBrush(QColor(220, 20, 60));
const QBrush firebrick = QBrush(QColor(178, 34, 34));
const QBrush darkRed = QBrush(QColor(139, 0, 0));
const QBrush blue = QBrush(QColor(0, 0, 255));
const QBrush yellow = QBrush(QColor(255, 255, 0));
const QBrush cyan = QBrush(QColor(0, 255, 255));
const QBrush magenta = QBrush(QColor(255, 0, 255));
const QBrush black = QBrush(QColor(0, 0, 0));
const QBrush white = QBrush(QColor(255, 255, 255));
const QBrush gray = QBrush(QColor(169, 169, 169));
const QBrush lightGray = QBrush(QColor(211, 211, 211));
const QBrush darkGray = QBrush(QColor(105, 105, 105));
const QBrush orange = QBrush(QColor(255, 165, 0));
const QBrush purple = QBrush(QColor(128, 0, 128));
const QBrush pink = QBrush(QColor(255, 192, 203));
const QBrush brown = QBrush(QColor(165, 42, 42));
const QBrush teal = QBrush(QColor(0, 128, 128));
const QBrush lime = QBrush(QColor(0, 255, 0));
const QBrush olive = QBrush(QColor(128, 128, 0));
const QBrush coral = QBrush(QColor(255, 127, 80));
const QBrush gold = QBrush(QColor(255, 215, 0));
const QBrush silver = QBrush(QColor(192, 192, 192));
const QBrush mint = QBrush(QColor(189, 252, 201));
const QBrush salmon = QBrush(QColor(250, 128, 114));
const QBrush lavender = QBrush(QColor(230, 230, 250));
const QBrush peach = QBrush(QColor(255, 218, 185));
const QBrush turquoise = QBrush(QColor(64, 224, 208));
const QBrush indigo = QBrush(QColor(75, 0, 130));
const QBrush violet = QBrush(QColor(238, 130, 238));
const QBrush chartreuse = QBrush(QColor(127, 255, 0));
const QBrush lightBlue = QBrush(QColor(173, 216, 230));
const QBrush skyBlue = QBrush(QColor(135, 206, 235));
const QBrush deepSkyBlue = QBrush(QColor(0, 191, 255));
const QBrush dodgerBlue = QBrush(QColor(30, 144, 255));
const QBrush royalBlue = QBrush(QColor(65, 105, 225));
const QBrush mediumBlue = QBrush(QColor(0, 0, 205));
const QBrush navy = QBrush(QColor(0, 0, 128));
const QBrush aqua = QBrush(QColor(0, 255, 255));
const QBrush brightBlue = QBrush(QColor(0, 0, 255));
const QBrush steelBlue = QBrush(QColor(70, 130, 180));
const QBrush powderBlue = QBrush(QColor(176, 224, 230));
const QBrush darkGreen = QBrush(QColor(0, 100, 0));
const QBrush forestGreen = QBrush(QColor(34, 139, 34));
const QBrush seaGreen = QBrush(QColor(46, 139, 87));
const QBrush oliveDrab = QBrush(QColor(107, 142, 35));
const QBrush lightGreen = QBrush(QColor(144, 238, 144));
const QBrush paleGreen = QBrush(QColor(152, 251, 152));
const QBrush springGreen = QBrush(QColor(0, 255, 127));
const QBrush mediumSpringGreen = QBrush(QColor(0, 250, 154));

} // namespace clr

#ifdef __clang__
const string COMPILER = "LLVM Clang";
#elif defined(__GNUC__) || defined(__GNUG__)
const string COMPILER = "GNU G++";
#elif defined(_MSC_VER)
const string COMPILER = "microsoft msvc";
#elif defined(__INTEL_COMPILER)
const string COMPILER = "Intel C++ Compiler";
#else
const string COMPILER = "Unknown compiler";
#endif