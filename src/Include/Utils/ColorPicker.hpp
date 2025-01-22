#pragma once

#include <QColor>
#include <QWidget>

class ColorPicker {
  public:
    static QColor ShowAndGet(QWidget *parent = nullptr, const QColor &initialColor = QColor());
};
