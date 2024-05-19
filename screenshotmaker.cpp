#include <QApplication>
#include <QFileDialog>
#include <QPixmap>

#include "menu.h"
#include "screenshotmaker.h"
#include "defines.h"

ScreenShotMaker::ScreenShotMaker(MainWidget *menu)
    : QWidget()
{
    this->menu = menu;
    setWindowOpacity(1);
    setGeometry(QApplication::primaryScreen()->geometry());

    screen = new Screen(this);
    screen->setGeometry(rect());
}

void ScreenShotMaker::activate()
{
    screen->setPixmap(QApplication::primaryScreen()->grabWindow());
#ifdef SSMAKER_WINDOW
    show();
#else
    showFullScreen();
#endif
}

void ScreenShotMaker::makeScreenShot(const QString &dir)
{
    if(!dir.isNull()) {
        if(dir == "NULL") {
            screen->grabScreenShotArea().save(menu->fileDir.dir() + "test" + menu->fileDir.fileExt());
        }
        else {
            screen->grabScreenShotArea().save(dir);
            qDebug() << dir;
        }
    }
    else {
        qDebug() << "dir - empty";
    }
}

void ScreenShotMaker::close()
{
    reset();
    static_cast<QWidget*> (this)->close();
}

void ScreenShotMaker::reset()
{
    screen->reset();
}

Screen::Screen(ScreenShotMaker *parent)
    : QLabel(parent)
{
    SSMaker = parent;

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
    SSArea->setStyleSheet(ScreenShotArea::borderStyles);
    SSArea->hide();

    toolBar = new ToolBar(this, parent);
    toolBar->setStyleSheet("background-color: rgb(200, 200, 200);"
                           "border: 1px solid black;");
    toolBar->hide();

    update();
}

void Screen::reset()
{
    gb_1->setGeometry(0, 0, width() / 2, height() / 2);
    gb_2->setGeometry(width() / 2, 0, width() / 2, height() / 2);
    gb_3->setGeometry(0, height() / 2, width() / 2, height() / 2);
    gb_4->setGeometry(width() / 2, height() / 2, width() / 2, height() / 2);
    SSArea->hide();
    toolBar->hide();
}

void Screen::updateToolsBarPos()
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
void Screen::moveToolBarLeftUp()
{
    toolBar->move(SSArea->x() - tbIndent - toolBar->width(), SSArea->y());
}

void Screen::moveToolBarLeftDown()
{
    toolBar->move(SSArea->x() - tbIndent - toolBar->width(), SSArea->y() + SSArea->height() - tbIndent - toolBar->height());
}

void Screen::moveToolBarUpLeft()
{
    if(SSArea->y() - toolBar->height() - tbIndent < y()) {
        toolBar->move(SSArea->x() + tbIndent, SSArea->y() + tbIndent);
    }
    else {
        toolBar->move(SSArea->x(), SSArea->y() - tbIndent - toolBar->height());
    }
}

void Screen::moveToolBarUpRight()
{
    if(SSArea->y() - toolBar->height() - tbIndent < y()) {
        toolBar->move(SSArea->x() + SSArea->width() - toolBar->width() - tbIndent, SSArea->y() + tbIndent);
    }
    else {
        toolBar->move(SSArea->x() + SSArea->width() - toolBar->width(), SSArea->y() - tbIndent - toolBar->height());
    }
}

void Screen::moveToolBarRightUp()
{
    toolBar->move(SSArea->x() + SSArea->width() + tbIndent, SSArea->y());
}

void Screen::moveToolBarRightDown()
{
    toolBar->move(SSArea->x() + SSArea->width() + tbIndent, SSArea->y() + SSArea->height() - toolBar->height());
}

void Screen::moveToolBarDownLeft()
{
    if(SSArea->x() + SSArea->width() + toolBar->height() + tbIndent > width()) {
        toolBar->move(SSArea->x() + tbIndent, SSArea->y() + SSArea->height() - tbIndent - toolBar->height());
    }
    else {
        toolBar->move(SSArea->x(), SSArea->y() + SSArea->height() + tbIndent);
    }
}

void Screen::moveToolBarDownRight()
{
    if(SSArea->y() + SSArea->height() + toolBar->height() + tbIndent > height()) {
        toolBar->move(SSArea->x() + SSArea->width() - toolBar->width() - tbIndent, SSArea->y() + SSArea->height() - toolBar->height() - tbIndent);
    }
    else {
        toolBar->move(SSArea->x() + SSArea->width() - toolBar->width(), SSArea->y() + SSArea->height() + tbIndent);
    }
}

QPixmap Screen::grabScreenShotArea()
{
    SSArea->setStyleSheet("border: 0px;");
    QPixmap pm = grab(QRect(SSArea->x(), SSArea->y(), SSArea->width(), SSArea->height()));
    SSArea->setStyleSheet(ScreenShotArea::borderStyles);
    return pm;
}

void Screen::resizeEvent(QResizeEvent *e)
{
    gb_1->setGeometry(0, 0, width() / 2, height() / 2);
    gb_2->setGeometry(width() / 2, 0, width() / 2, height() / 2);
    gb_3->setGeometry(0, height() / 2, width() / 2, height() / 2);
    gb_4->setGeometry(width() / 2, height() / 2, width() / 2, height() / 2);
}

void Screen::mousePressEvent(QMouseEvent *e)
{
    toolBar->hide();
    SSArea->show();
    if(e->buttons() == Qt::LeftButton) {
        gb_1->resize(e->pos().x(), e->pos().y());
        gb_2->setGeometry(gb_1->width(), 0, width(), e->pos().y());
        gb_3->setGeometry(0, e->pos().y(), e->pos().x(), height());
        gb_4->setGeometry(e->pos().x(), e->pos().y(), width(), height());
        SSArea->setGeometry(gb_4->x(), gb_3->y(), gb_1->width() - gb_4->x(), gb_2->height() - gb_3->y());
        SSArea->show();
    }
}

void Screen::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << SSArea->rect();
    toolBar->show();
    updateToolsBarPos();
}

void Screen::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() == Qt::LeftButton) {
        expScreenArea(e);
    }
}

void Screen::expScreenArea(QMouseEvent *e)
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

void Screen::expScreenAreaLeft(QMouseEvent *e)
{
    gb_3->resize(e->pos().x(), height());
    gb_4->move(e->pos().x(), gb_4->y());
}

void Screen::expScreenAreaRight(QMouseEvent *e)
{
    gb_1->resize(e->pos().x(), gb_1->height());
    gb_2->move(e->pos().x(), 0);
}

void Screen::expScreenAreaUp(QMouseEvent *e)
{
    gb_1->resize(gb_1->width(), e->pos().y());
    gb_3->move(0, e->pos().y());
}

void Screen::expScreenAreaDown(QMouseEvent *e)
{
    gb_2->resize(gb_2->width(), e->pos().y());
    gb_4->move(gb_4->x(), e->pos().y());
}

ScreenShotArea::ScreenShotArea(Screen *sa)
    : QGroupBox(sa)
{
    parent = sa;
}

void ScreenShotArea::makeScreenShot()
{

}

void ScreenShotArea::resizeEvent(QResizeEvent *e)
{

}

ToolBar::ToolBar(Screen *parent, ScreenShotMaker *ssm)
    : QGroupBox(parent)
{
    this->parent = parent;
    SSMaker = ssm;

    setCursor(QCursor(Qt::PointingHandCursor));
    resize(30, 90);

    fastSavePB = new QPushButton("fast", this);
    connect(fastSavePB, &QPushButton::clicked, this, &ToolBar::fastSavePBClicked);

    savePB = new QPushButton("save", this);
    connect(savePB, &QPushButton::clicked, this, &ToolBar::savePBClicked);

    closePB = new QPushButton("X", this);
    connect(closePB, &QPushButton::clicked, this, &ToolBar::closePBClicked);
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
        resize(90, 30);
    }
    else {
        isVertical = true;
        resize(30, 90);
    }
}

void ToolBar::resizeEvent(QResizeEvent *e)
{
    if(isVertical) {
        fastSavePB->resize(width(), width());
        savePB->setGeometry(0, fastSavePB->y() + width(), width(), width());
        closePB->setGeometry(0, savePB->y() + width(), width(), width());
    }
    else {
        fastSavePB->resize(height(), height());
        savePB->setGeometry(fastSavePB->x() + height(), 0, height(), height());
        closePB->setGeometry(savePB->x() + height(), 0, height(), height());
    }
}

void ToolBar::fastSavePBClicked()
{
    SSMaker->makeScreenShot();
    SSMaker->close();
}

void ToolBar::savePBClicked()
{
    SSMaker->makeScreenShot(QFileDialog::getSaveFileName(this, "Выберите директорию", FileConfig::dir(), FileConfig::EXT_LIST));
    SSMaker->close();
}

void ToolBar::closePBClicked()
{
    SSMaker->close();
}
