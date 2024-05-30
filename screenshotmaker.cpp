#include <QApplication>
#include <QFile>
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
            QString filePath = menu->fileDir.dir() + "Screenshot" + menu->fileDir.fileExt(); // полный путь к файлу, который хотим создать

            for(size_t i = 1; QFile::exists(filePath); ++i) {                                // бегаем по циклу, пока filePath уже существует
                filePath = menu->fileDir.dir() + "Screenshot_" +
                           QString::number(i)  + menu->fileDir.fileExt();                    // меняем имя файла
            }
            screen->grabScreenShotArea().save(filePath);
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

    toolBarPin = Pin(toolBar, SSArea);

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
            if(toolBarPin.checkLeftUp().x() >= x()) {
                toolBar->setVertical();
                toolBarPin.setOut(true);
                toolBarPin.moveLeftUp();
            }
            else {
                toolBar->setHorizontal();
                toolBarPin.setOut(false);
                toolBarPin.moveUpLeft();
            }
        }
        else {
            if(toolBarPin.checkLeftDown().x() >= x()) {
                toolBar->setVertical();
                toolBarPin.setOut(true);
                toolBarPin.moveLeftDown();
            }
            else {
                toolBar->setHorizontal();
                toolBarPin.setOut(false);
                toolBarPin.moveDownLeft();
            }
        }
    }
    else {
        if(changeY) {
            if(toolBarPin.checkRightUp().x() <= width()) {
                toolBar->setVertical();
                toolBarPin.setOut(true);
                toolBarPin.moveRightUp();
            }
            else {
                toolBar->setHorizontal();
                toolBarPin.setOut(false);
                toolBarPin.moveUpRight();
            }
        }
        else {
            if(toolBarPin.checkRightDown().x() <= width()) {
                toolBar->setVertical();
                toolBarPin.setOut(true);
                toolBarPin.moveRightDown();
            }
            else {
                toolBar->setHorizontal();
                toolBarPin.setOut(false);
                toolBarPin.moveDownRight();
            }
        }
    }
}

QPixmap Screen::grabScreenShotArea()
{
    SSArea->setStyleSheet("border: 0px;");
    toolBar->hide();
    QPixmap pm = grab(QRect(SSArea->x(), SSArea->y(), SSArea->width(), SSArea->height()));
    toolBar->show();
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

ShowRect::ShowRect(QWidget *parent, const QWidget *obj)
    : QLabel(parent)
{
    this->obj = obj;
    this->parent = parent;
    setText(QString::number(obj->width()) + "x" + QString::number(obj->width()));
    setAlignment(Qt::AlignCenter);
}

void ShowRect::update()
{
    setText(QString::number(obj->width()) + "x" + QString::number(obj->width()));
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
