#include "showrect.h"

ShowRect::ShowRect(QWidget *parent, const QWidget *obj)
    : QLabel(parent), obj(obj)
{
    setText(QString::number(obj->width()) + "x" + QString::number(obj->height()));
    setAlignment(Qt::AlignCenter);
}

void ShowRect::update()
{
    setText(QString::number(obj->width()) + "x" + QString::number(obj->height()));
    updateWidth();
}

void ShowRect::updateWidth()
{
    if(text().size() <= 5) {
        resize(font().pointSize() * text().size() * 0.9, height());
    }
    else {
        resize(font().pointSize() * text().size() * 0.8, height());
    }
}
