#include "pin.h"

Pin &Pin::operator =(const Pin &pin)
{
    pinner = pin.pinner;
    obj = pin.obj;
    indent = pin.indent;
    placement = pin.placement;
    return *this;
}

void Pin::update()
{
    switch (placement) {
    case LeftUp:
        moveLeftUp();
        break;
    case LeftDown:
        moveLeftDown();
        break;
    case UpLeft:
        moveUpLeft();
        break;
    case UpRight:
        moveUpRight();
        break;
    case RightUp:
        moveRightUp();
        break;
    case RightDown:
        moveRightDown();
        break;
    case DownLeft:
        moveDownLeft();
        break;
    case DownRight:
        moveDownRight();
        break;
    default:
        break;
    }
}

void Pin::moveLeftUp()
{
    pinner->move(checkLeftUp());
    placement = LeftUp;
}

void Pin::moveLeftDown()
{
    pinner->move(checkLeftDown());
    placement = LeftDown;
}

void Pin::moveUpLeft()
{
    pinner->move(checkUpLeft());
    placement = UpLeft;
}

void Pin::moveUpRight()
{
    pinner->move(checkUpRight());
    placement = UpRight;
}

void Pin::moveRightUp()
{
    pinner->move(checkRightUp());
    placement = RightUp;
}

void Pin::moveRightDown()
{
    pinner->move(checkRightDown());
    placement = RightDown;
}

void Pin::moveDownLeft()
{
    pinner->move(checkDownLeft());
    placement = DownLeft;
}

void Pin::moveDownRight()
{
    pinner->move(checkDownRight());
    placement = DownRight;
}

QPoint Pin::checkLeftUp()
{
    QPoint pos;
    if(isOut) {
        pos = QPoint(obj->x() - indent - pinner->width(), obj->y());
    }
    else {
        pos = QPoint(obj->x() + indent, obj->y() + indent);
    }
    return pos;
}

QPoint Pin::checkLeftDown()
{
    QPoint pos;
    if(isOut) {
        pos = QPoint(obj->x() - indent - pinner->width(), obj->y() + obj->height() - indent - pinner->height());
    }
    else {
        pos = QPoint(obj->x() + indent, obj->y() + obj->height() - indent - pinner->height());
    }
    return pos;
}

QPoint Pin::checkUpLeft()
{
    QPoint pos;
    if(isOut) {
        pos = QPoint(obj->x(), obj->y() - indent - pinner->height());
    }
    else {
        pos = QPoint(obj->x() + indent, obj->y() + indent);
    }
    return pos;
}

QPoint Pin::checkUpRight()
{
    QPoint pos;
    if(isOut) {
        pos = QPoint(obj->x() + obj->width() - pinner->width(), obj->y() - indent - pinner->height());
    }
    else {
        pos = QPoint(obj->x() + obj->width() - pinner->width() - indent, obj->y() + indent);
    }
    return pos;
}

QPoint Pin::checkRightUp()
{
    QPoint pos;
    if(isOut) {
        pos = QPoint(obj->x() + obj->width() + indent, obj->y());
    }
    else {
        pos = QPoint(obj->x() + obj->width() - pinner->width() - indent, obj->y() + indent);
    }
    return pos;
}

QPoint Pin::checkRightDown()
{
    QPoint pos;
    if(isOut) {
        pos = QPoint(obj->x() + obj->width() + indent, obj->y() + obj->height() - pinner->height());
    }
    else {
        pos = QPoint(obj->x() + obj->width() - pinner->width() - indent, obj->y() + obj->height() - pinner->height() - indent);
    }
    return pos;
}

QPoint Pin::checkDownLeft()
{
    QPoint pos;
    if(isOut) {
        pos = QPoint(obj->x(), obj->y() + obj->height() + indent);
    }
    else {
        pos = QPoint(obj->x() + indent, obj->y() + obj->height() - pinner->height() - indent);
    }
    return pos;
}

QPoint Pin::checkDownRight()
{
    QPoint pos;
    if(isOut) {
        pos = QPoint(obj->x() + obj->width() - pinner->width(), obj->y() + obj->height() + indent);
    }
    else {
        pos = QPoint(obj->x() + obj->width() - pinner->width() - indent, obj->y() + obj->height() - pinner->height() - indent);
    }
    return pos;
}
