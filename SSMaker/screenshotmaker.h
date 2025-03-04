#ifndef SCREENSHOTMAKER_H
#define SCREENSHOTMAKER_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QClipboard>
#include <QApplication>

#include "pin.h"
#include "showrect.h"
#include "hintbutton.h"
#include "keys.h"
#include "KeyShortcut.h"

class MainWidget;
class Screen;
class ScreenShotArea;   // зона скриншота
class ToolBar;          // инструменты для взаимодействия с ScreenShotArea

class ScreenShotMaker : public QWidget
{
public:
    ScreenShotMaker();

    void activate();
    void makeScreenShot(const QString &dir = "NULL");
    void close();
    void reset();

private:
    Screen *screen;
};

class Screen : public QLabel
{
    Q_OBJECT
public:
    explicit Screen(ScreenShotMaker *parent);

    void reset();

    void updateToolsBarPos();
    void updateSSAreaRectPos();

    inline void hideSSAreaRect() { SSAreaRect->hide(); }

    QPixmap grabScreenShotArea();

    void copyToClipboard();

private slots:
    void resizeEvent(QResizeEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

    void keyPressEvent(QKeyEvent *e)   override;
    void keyReleaseEvent(QKeyEvent *e) override;

private:
    void expScreenArea(QMouseEvent *e);
    void expScreenAreaLeft(QMouseEvent *e);              // изменяют размеры gb_ согласно позиции мыши
    void expScreenAreaRight(QMouseEvent *e);            // оставляют не затемненную зону для ScreenShotArea
    void expScreenAreaUp(QMouseEvent *e);
    void expScreenAreaDown(QMouseEvent *e);

    ScreenShotMaker *SSMaker;

    QGroupBox *gb_1; // создают затемнённую область
    QGroupBox *gb_2;
    QGroupBox *gb_3;
    QGroupBox *gb_4;

    ScreenShotArea *SSArea;
    ToolBar *toolBar;
    ShowRect *SSAreaRect;

    Pin toolBarPin;
    Pin SSAreaRectPin;

    KeyShortcut<Screen> shortcut{ Qt::Key_Control, Qt::Key_C };

// Отвечают, какой параметр будет изменяться у ScreenShotArea при перемещении мыши
    bool changeY; // true - менятся позиция по y, false - меняться height
    bool changeX; // true - менятся позиция по x, false - меняться width

    const quint8 GB_OPACITY = 100; // прозрачность затемнения 0 - 255
};

class ScreenShotArea : public QGroupBox
{
    Q_OBJECT
public:
    ScreenShotArea(Screen *sa);

    const static inline QString borderStyles = "border: 2px dashed grey;";
private slots:
    void resizeEvent(QResizeEvent *e) override;

private:
    Screen *parent;
};

class ToolBar : public QGroupBox
{
    Q_OBJECT
public:
    ToolBar(Screen *parent, ScreenShotMaker *ssm);

    void setVertical(); // расположить вертикально/горизонтально
    void setHorizontal();

    void rotate(); // повернуть

private slots:
    void resizeEvent(QResizeEvent *e) override;

    void fastSavePBClicked(); // быстрое сохранение скрина с настройками конфига
    void savePBClicked();     // выбор пути, имени и расширения файла
    void saveClipboardPBClicked();
    void closePBClicked();

private:
    Screen *screen;
    ScreenShotMaker *SSMaker;

    HintButton *fastSavePB;
    HintButton *savePB;
    HintButton *saveClipboardPB;
    HintButton *closePB;

    bool isVertical = true; // true - вертикально расположен, false - горизонтально
};

#endif // SCREENSHOTMAKER_H
