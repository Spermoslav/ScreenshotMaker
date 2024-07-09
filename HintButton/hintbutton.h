#ifndef HINTBUTTON_H
#define HINTBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QString>
#include <QEnterEvent>
#include <QTimer>

// Используется как кнопка, при наведении курсора на которую появляется подсказка QLabel
// QLabel распологается около курсора

class HintButton : public QPushButton
{
    Q_OBJECT
public:
    explicit HintButton(QWidget* btnpar = nullptr, QWidget* hintpar = nullptr);
    explicit HintButton(const QString& text, QWidget* btnpar = nullptr, QWidget* hintpar = nullptr);
    HintButton(const QString& text, const QString& hint, QWidget* btnpar = nullptr, QWidget* hintpar = nullptr);

    void setInterval(uint time);
    void setHint(const QString& hint);
    void setHintParent(QWidget* parent);
    void setHintIndent(int ind);
    void setHintContentsMargins(int left, int top, int right, int down);
    void setHintStyleSheet(const QString& style);

    inline QString hint() const { return hintL->text(); }

protected:
    void mouseMoveEvent(QMouseEvent* e);
    bool eventFilter(QObject *obj, QEvent *event);

private slots:
    void showHint();

private:
    bool checkLeft();     // Проверяют, с какой стороны от курсора можно разместить QLabel
    bool checkUp();
    bool checkRight();
    bool checkDown();

    void moveHint();
    void moveHintLeft();  // Размещают QLabel слева/справа и внизу/вверху от курсора
    void moveHintUp();
    void moveHintRight();
    void moveHintDown();

    QTimer* showHintTimer;

    QLabel* hintL;

    int hintIndent = 1;    // отступ от курсора

    bool cursorIn = false; // Курсор внутри кнопки - true
};

#endif // HINTBUTTON_H
