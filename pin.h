#ifndef PIN_H
#define PIN_H

#include <QWidget>
#include <QPoint>

enum Placement
{
    LeftUp,
    LeftDown,
    UpLeft,
    UpRight,
    RightUp,
    RightDown,
    DownLeft,
    DownRight
};

// Класс Pin служит для закрепления одного виджета к другому.
// Располагает объект слева/вверху/справа/внизу и внутри/снаружи от другого объекта
class Pin
{
public:
    Pin() = default;
    Pin(QWidget* pinner, const QWidget* obj, uint indent = 10, Placement place = UpLeft);
    Pin &operator = (const Pin &pin);

    void setOut(bool out) { isOut = out; }

    void update();          // обновляет позицию pinner

    void moveLeftUp();      // перемещают pinner слева/вверху/справа/внизу и внутри/снаружи
    void moveLeftDown();
    void moveUpLeft();
    void moveUpRight();
    void moveRightUp();
    void moveRightDown();
    void moveDownLeft();
    void moveDownRight();

    QPoint checkLeftUp();      // возвращают будущую позицию pinner
    QPoint checkLeftDown();
    QPoint checkUpLeft();
    QPoint checkUpRight();
    QPoint checkRightUp();
    QPoint checkRightDown();
    QPoint checkDownLeft();
    QPoint checkDownRight();

    uint getIndent() const { return indent; }

private:
    QWidget* pinner;        // объект, который прикрепляется
    const QWidget* obj;     // объект, к которому прикрепляются
    uint indent = 0;        // отступ от obj
    Placement placement;    // расположение pinner
    bool isOut = true;      // расположение внутри(false)/снаружи(true)
};

#endif // PIN_H
