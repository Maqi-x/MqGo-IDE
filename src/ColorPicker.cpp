#include <QColorDialog>
#include <Utils/ColorPicker.hpp>

QColor ColorPicker::ShowAndGet(QWidget *parent, const QColor &initialColor) {
    QColor color = QColorDialog::getColor(initialColor, parent);
    return color.isValid() ? color : QColor(0, 0, 0);
}
