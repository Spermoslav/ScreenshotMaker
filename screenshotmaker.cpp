#include "screenshotmaker.h"
#include <QApplication>

ScreenShotMaker::ScreenShotMaker()
    : QWidget()
{
    setWindowOpacity(1);
    setGeometry(QApplication::primaryScreen()->geometry());

    screen = new DarkArea(this);
    screen->setGeometry(rect());
}

void ScreenShotMaker::activate()
{
    screen->setPixmap(QApplication::primaryScreen()->grabWindow());
    show();
}

DarkArea::DarkArea(QWidget *parent)
    : QLabel(parent)
{
    gb_1 = new QGroupBox(this);
    gb_1->setGeometry(0, 0, width() / 2, height() / 2);
    gb_1->setStyleSheet("background-color: rgba(0, 0, 0, " + QString::number(GB_OPACITY) + ");"
                        "border: 0px;");

    gb_2 = new QGroupBox(this);
    gb_2->setGeometry(width() / 2, 0, width() / 2, height() / 2);
    gb_2->setStyleSheet("background-color: rgba(0, 0, 0, " + QString::number(GB_OPACITY) + ");"
                        "border: 0px;");

    gb_3 = new QGroupBox(this);
    gb_3->setGeometry(0, height() / 2, width() / 2, height() / 2);
    gb_3->setStyleSheet("background-color: rgba(0, 0, 0, " + QString::number(GB_OPACITY) + ");"
                        "border: 0px;");

    gb_4 = new QGroupBox(this);
    gb_4->setGeometry(width() / 2, height() / 2, width() / 2, height() / 2);
    gb_4->setStyleSheet("background-color: rgba(0, 0, 0, " + QString::number(GB_OPACITY) + ");"
                        "border: 0px;");

    SSArea = new ScreenShotArea(this);
    SSArea->setStyleSheet("border: 2px dashed grey;");
    SSArea->hide();

    toolBar = new ToolBar(this);
    toolBar->setStyleSheet("border: 1px solid black;");
    toolBar->hide();
}

void DarkArea::show()
{
    static_cast<QLabel*> (this)->show();
}

void DarkArea::updateToolsBarPos()
{

    if(changeX) {
        if(changeY) {
            if(SSArea->x() - tbIndent - toolBar->width() >= x()) {
                toolBar->setVertical();
                moveToolBarLeftUp();
            }
            else {
                toolBar->setHorizontal();
                moveToolBarUpLeft();
            }
        }
        else {
            if(SSArea->x() - tbIndent - toolBar->width() >= x()) {
                toolBar->setVertical();
                moveToolBarLeftDown();
            }
            else {
                toolBar->setHorizontal();
                moveToolBarDownLeft();
            }
        }
    }
    else {
        if(changeY) {
            if(SSArea->x() + SSArea->width() + tbIndent + toolBar->width() <= width()) {
                toolBar->setVertical();
                moveToolBarRightUp();
            }
            else {
                toolBar->setHorizontal();
                moveToolBarUpRight();
            }
        }
        else {
            if(SSArea->x() + SSArea->width() + tbIndent + toolBar->width() <= width()) {
                toolBar->setVertical();
                moveToolBarRightDown();
            }
            else {
                toolBar->setHorizontal();
                moveToolBarDownRight();
            }
        }
    }
}
void DarkArea::moveToolBarLeftUp()
{
    toolBar->move(SSArea->x() - tbIndent - toolBar->width(), SSArea->y());
}

void DarkArea::moveToolBarLeftDown()
{
    toolBar->move(SSArea->x() - tbIndent - toolBar->width(), SSArea->y() + SSArea->height() - tbIndent - toolBar->height());
}

void DarkArea::moveToolBarUpLeft()
{
    if(SSArea->y() - toolBar->height() - tbIndent < y()) {
        toolBar->move(SSArea->x() + tbIndent, SSArea->y() + tbIndent);
    }
    else {
        toolBar->move(SSArea->x(), SSArea->y() - tbIndent - toolBar->height());
    }
}

void DarkArea::moveToolBarUpRight()
{
    if(SSArea->y() - toolBar->height() - tbIndent < y()) {
        toolBar->move(SSArea->x() + SSArea->width() - toolBar->width() - tbIndent, SSArea->y() + tbIndent);
    }
    else {
        toolBar->move(SSArea->x() + SSArea->width() - toolBar->width(), SSArea->y() - tbIndent - toolBar->height());
    }
}

void DarkArea::moveToolBarRightUp()
{
    toolBar->move(SSArea->x() + SSArea->width() + tbIndent, SSArea->y());
}

void DarkArea::moveToolBarRightDown()
{
    toolBar->move(SSArea->x() + SSArea->width() + tbIndent, SSArea->y() + SSArea->height() - toolBar->height());
}

void DarkArea::moveToolBarDownLeft()
{
    if(SSArea->x() + SSArea->width() + toolBar->height() + tbIndent > width()) {
        toolBar->move(SSArea->x() + tbIndent, SSArea->y() + SSArea->height() - tbIndent - toolBar->height());
    }
    else {
        toolBar->move(SSArea->x(), SSArea->y() + SSArea->height() + tbIndent);
    }
}

void DarkArea::moveToolBarDownRight()
{
    if(SSArea->y() + SSArea->height() + toolBar->height() + tbIndent > height()) {
        toolBar->move(SSArea->x() + SSArea->width() - toolBar->width() - tbIndent, SSArea->y() + SSArea->height() - toolBar->height() - tbIndent);
    }
    else {
        toolBar->move(SSArea->x() + SSArea->width() - toolBar->width(), SSArea->y() + SSArea->height() + tbIndent);
    }
}

void DarkArea::resizeEvent(QResizeEvent *e)
{
    gb_1->setGeometry(0, 0, width() / 2, height() / 2);
    gb_2->setGeometry(width() / 2, 0, width() / 2, height() / 2);
    gb_3->setGeometry(0, height() / 2, width() / 2, height() / 2);
    gb_4->setGeometry(width() / 2, height() / 2, width() / 2, height() / 2);
}

void DarkArea::mousePressEvent(QMouseEvent *e)
{
    toolBar->hide();
    prevMousePos = e->pos();
    if(e->buttons() == Qt::LeftButton) {
        gb_1->resize(e->pos().x(), e->pos().y());
        gb_2->setGeometry(gb_1->width(), 0, width(), e->pos().y());
        gb_3->setGeometry(0, e->pos().y(), e->pos().x(), height());
        gb_4->setGeometry(e->pos().x(), e->pos().y(), width(), height());
        SSArea->setGeometry(gb_4->x(), gb_3->y(), gb_1->width() - gb_4->x(), gb_2->height() - gb_3->y());
        SSArea->show();
    }
}

void DarkArea::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << SSArea->rect();
    toolBar->show();
    updateToolsBarPos();
}

void DarkArea::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton) {
        expScreenArea(e);
    }
}

void DarkArea::expScreenArea(QMouseEvent *e)
{
    if(e->pos().x() > gb_2->x()) {
        expScreenAreaRight(e);
        changeX = false;
    }
    else if(e->pos().x() < gb_4->x()) {
        expScreenAreaLeft(e);
        changeX = true;
    }
    else if(e->pos().x() > gb_4->x() && e->pos().x() < gb_2->x()) {
        if(changeX) {
            expScreenAreaLeft(e);
        }
        else {
            expScreenAreaRight(e);
        }
    }

    if(e->pos().y() > gb_4->y()) {
        expScreenAreaDown(e);
        changeY = false;
    }
    else if(e->pos().y() < gb_3->y()) {
        expScreenAreaUp(e);
        changeY = true;
    }
    else if(e->pos().y() > gb_3->y() && e->pos().y() < gb_4->y()) {
        if(changeY) {
            expScreenAreaUp(e);
        }
        else {
            expScreenAreaDown(e);
        }
    }
    SSArea->setGeometry(gb_4->x(), gb_3->y(), gb_1->width() - gb_4->x(), gb_2->height() - gb_3->y());
}

void DarkArea::expScreenAreaLeft(QMouseEvent *e)
{
    gb_3->resize(e->pos().x(), height());
    gb_4->move(e->pos().x(), gb_4->y());
}

void DarkArea::expScreenAreaRight(QMouseEvent *e)
{
    gb_1->resize(e->pos().x(), gb_1->height());
    gb_2->move(e->pos().x(), 0);
}

void DarkArea::expScreenAreaUp(QMouseEvent *e)
{
    gb_1->resize(gb_1->width(), e->pos().y());
    gb_3->move(0, e->pos().y());
}

void DarkArea::expScreenAreaDown(QMouseEvent *e)
{
    gb_2->resize(gb_2->width(), e->pos().y());
    gb_4->move(gb_4->x(), e->pos().y());
}

ScreenShotArea::ScreenShotArea(DarkArea *sa)
    : QGroupBox(sa)

{
    parent = sa;
}

void ScreenShotArea::resizeEvent(QResizeEvent *e)
{

}

ToolBar::ToolBar(DarkArea *parent)
    : QGroupBox(parent)
{
    this->parent = parent;
    resize(30, 200);

    btn1 = new QPushButton("frst", this);
    btn2 = new QPushButton("sec", this);

}

void ToolBar::setVertical()
{
    if(!isVertical) rotate();
}

void ToolBar::setHorizontal()
{
    if(isVertical) rotate();
}

void ToolBar::rotate()
{
    if(isVertical) {
        isVertical = false;
        resize(200, 30);
    }
    else {
        isVertical = true;
        resize(30, 200);
    }
}

void ToolBar::resizeEvent(QResizeEvent *e)
{
    if(isVertical) {
        btn1->resize(width(), width());
        btn2->setGeometry(0, width(), width(), width());
    }
    else {
        btn1->resize(height(), height());
        btn2->setGeometry(height(), 0, height(), height());
    }
}

