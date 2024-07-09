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
#ifndef SSMAKER_NOTTOPHINT
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
#endif
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

    SSAreaRect = new ShowRect(this, SSArea);
    SSAreaRect->setStyleSheet("border: 1px solid black;"
                              "border-radius: 7px;"
                              "background-color: rgb(200, 200, 200);");
    SSAreaRect->setFont(QFont(SSAreaRect->font().family(), 20));
    SSAreaRect->hide();

    toolBarPin = Pin(toolBar, SSArea);

    SSAreaRectPin = Pin(SSAreaRect, SSArea);

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
    SSAreaRect->hide();
}

void Screen::updateToolsBarPos()
{
    toolBarPin.setOut(true);
    if(changeX) {
        if(changeY) {
            if(toolBarPin.checkLeftUp().x() >= x()) {
                toolBar->setVertical();
                toolBarPin.moveLeftUp();
            }
            else {
                if(SSAreaRectPin.place() == UpLeft) {
                    if(toolBarPin.checkRightDown().x() + toolBar->width() <= width()) {
                        toolBar->setVertical();
                        toolBarPin.moveRightDown();
                    }
                    else if(toolBarPin.checkDownRight().y() + toolBar->height() <= height()) {
                        toolBar->setHorizontal();
                        toolBarPin.moveDownRight();
                    }
                    else {
                        toolBar->setHorizontal();
                        toolBarPin.setOut(false);
                        toolBarPin.moveDownRight();
                    }

                }
                else toolBarPin.moveUpLeft();
            }
        }
        else {
            if(toolBarPin.checkLeftDown().x() >= x()) {
                toolBar->setVertical();
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
                toolBarPin.moveRightUp();
            }
            else {
                toolBar->setHorizontal();
                toolBarPin.setOut(false);
                toolBarPin.moveUpRight();
            }
        }
        else {
            if(toolBarPin.checkRightDown().x() + toolBar->width() <= width()) {
                toolBar->setVertical();
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

void Screen::updateSSAreaRectPos()
{
    SSAreaRectPin.setOut(true);
    if(SSAreaRectPin.checkUpLeft().y() < 0) {
        SSAreaRectPin.setOut(false);
    }
    SSAreaRectPin.moveUpLeft();
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
        SSAreaRect->show();
        SSAreaRectPin.update();
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
        SSAreaRect->update();
        if(changeX || changeY ) updateSSAreaRectPos();
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
    : QGroupBox(parent), screen(parent), SSMaker(ssm),
    fastSavePB     (new HintButton("fast", this, parent)),
    savePB         (new HintButton("save", this, parent)),
    saveClipboardPB(new HintButton("copy", this, parent)),
    closePB        (new HintButton("close", this, parent))
{
    setCursor(QCursor(Qt::PointingHandCursor));
    resize(30, 120);

    fastSavePB->setHint("Быстрое сохранение в директорию\nпо умолчанию");
    fastSavePB->setHintContentsMargins(5, 5, 5, 5);
    fastSavePB->setHintStyleSheet("background-color: rgb(200, 200, 200);"
                                  "border: 1px solid black;"
                                  "border-radius: 5px;");
    savePB->setHint("Сохранить в директорию");
    savePB->setHintContentsMargins(5, 5, 5, 5);
    savePB->setHintStyleSheet("background-color: rgb(200, 200, 200);"
                              "border: 1px solid black;"
                              "border-radius: 5px;");
    saveClipboardPB->setHint("Копировать скриншот");
    saveClipboardPB->setHintContentsMargins(5, 5, 5, 5);
    saveClipboardPB->setHintStyleSheet("background-color: rgb(200, 200, 200);"
                                       "border: 1px solid black;"
                                       "border-radius: 5px;");
    closePB->setHint("Закрыть");
    closePB->setHintContentsMargins(5, 5, 5, 5);
    closePB->setHintStyleSheet("background-color: rgb(200, 200, 200);"
                               "border: 1px solid black;"
                               "border-radius: 5px;");

    connect(fastSavePB, &QPushButton::clicked, this, &ToolBar::fastSavePBClicked);
    connect(savePB, &QPushButton::clicked, this, &ToolBar::savePBClicked);
    connect(closePB, &QPushButton::clicked, this, &ToolBar::closePBClicked);
    connect(saveClipboardPB, &QPushButton::clicked, this, &ToolBar::saveClipboardPBClicked);
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
        resize(120, 30);
    }
    else {
        isVertical = true;
        resize(30, 120);
    }
}

void ToolBar::resizeEvent(QResizeEvent *e)
{
    if(isVertical) {
        fastSavePB->resize(width(), width());
        savePB->setGeometry(0, fastSavePB->y() + width(), width(), width());
        saveClipboardPB->setGeometry(0, savePB->y() + width(), width(), width());
        closePB->setGeometry(0, saveClipboardPB->y() + width(), width(), width());
    }
    else {
        fastSavePB->resize(height(), height());
        savePB->setGeometry(fastSavePB->x() + height(), 0, height(), height());
        saveClipboardPB->setGeometry(savePB->x() + height(), 0, height(), height());
        closePB->setGeometry(saveClipboardPB->x() + height(), 0, height(), height());
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

void ToolBar::saveClipboardPBClicked()
{
    QApplication::clipboard()->setPixmap(screen->grabScreenShotArea());
    SSMaker->close();
}

void ToolBar::closePBClicked()
{
    SSMaker->close();
}
