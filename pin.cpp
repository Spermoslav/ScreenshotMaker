#include "pin.h"

Pin::Pin(QWidget* pinner, const  QWidget* obj, uint indent, Placement place)
{
    this->pinner = pinner;
    this->obj = obj;
    this->indent = indent;
    placement = place;
}

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
    if(isOut) {
        pinner->move(obj->x() - indent - pinner->width(), obj->y());
    }
    else {
        pinner->move(obj->x() + indent, obj->y() + indent);
    }
    placement = LeftUp;
}

void Pin::moveLeftDown()
{
    if(isOut) {
        pinner->move(obj->x() - indent - pinner->width(), obj->y() + obj->height() - indent - pinner->height());
    }
    else {
        pinner->move(obj->x() + indent, obj->y() + obj->height() - indent - pinner->height());
    }
    placement = LeftDown;
}

void Pin::moveUpLeft()
{
    if(isOut) {
        pinner->move(obj->x(), obj->y() - indent - pinner->height());
    }
    else {
        pinner->move(obj->x() + indent, obj->y() + indent);
    }
    placement = UpLeft;
}

void Pin::moveUpRight()
{
    if(isOut) {
        pinner->move(obj->x() + obj->width() - pinner->width(), obj->y() - indent - pinner->height());
    }
    else {
        pinner->move(obj->x() + obj->width() - pinner->width() - indent, obj->y() + indent);
    }
    placement = UpRight;
}

void Pin::moveRightUp()
{
    if(isOut) {
        pinner->move(obj->x() + obj->width() + indent, obj->y());
    }
    else {
        pinner->move(obj->x() + obj->width() - pinner->width() - indent, obj->y() + indent);
    }
    placement = RightUp;
}

void Pin::moveRightDown()
{
    if(isOut) {
        pinner->move(obj->x() + obj->width() + indent, obj->y() + obj->height() - pinner->height());
    }
    else {
        pinner->move(obj->x() + obj->width() - pinner->width() - indent, obj->y() + obj->height() - pinner->height() - indent);
    }
    placement = RightDown;
}

void Pin::moveDownLeft()
{
    if(isOut) {
        pinner->move(obj->x(), obj->y() + obj->height() + indent);
    }
    else {
        pinner->move(obj->x() + indent, obj->y() + obj->height() - pinner->height() - indent);
    }
    placement = DownLeft;
}

void Pin::moveDownRight()
{
    if(isOut) {
        pinner->move(obj->x() + obj->width() - pinner->width(), obj->y() + obj->height() + indent);
    }
    else {
        pinner->move(obj->x() + obj->width() - pinner->width() - indent, obj->y() + obj->height() - pinner->height() - indent);
    }
    placement = DownRight;
}
