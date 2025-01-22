#ifndef EDITOR_HPP
#define EDITOR_HPP

#include <QKeyEvent>
#include <QPlainTextEdit>

class BaseGoEditor : public QPlainTextEdit {
    Q_OBJECT

  public:
    explicit BaseGoEditor(QWidget *parent = nullptr);

  protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif
