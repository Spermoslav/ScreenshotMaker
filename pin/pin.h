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
// Располагает объект слева/вверху/справа/внизу и внутри/снаружи от другого объекта рядом с его границей
class Pin
{
public:
    Pin() = default;
    inline Pin(QWidget* pinner, const QWidget* obj, uint indent = 10, Placement place = UpLeft)
        : pinner(pinner), obj(obj), indent(indent), placement(place) {}
    Pin &operator = (const Pin &pin);

    inline void setOut(bool out) { isOut = out; }

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

    inline uint getIndent() const { return indent; }

    inline Placement place() const { return placement; }

private:
    QWidget* pinner;        // объект, который прикрепляется
    const QWidget* obj;     // объект, к которому прикрепляются
    uint indent = 0;        // отступ от obj
    Placement placement;    // расположение pinner
    bool isOut = true;      // расположение внутри(false)/снаружи(true)
};

#endif // PIN_H
