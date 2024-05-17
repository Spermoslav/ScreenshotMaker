#ifndef SCREENSHOTMAKER_H
#define SCREENSHOTMAKER_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class DarkArea;
class ScreenShotArea; // зона скриншота
class ToolBar; // инструменты для взаимодействия с ScreenShotArea

class ScreenShotMaker : public QWidget
{
public:
    ScreenShotMaker();

    void activate();

private:
    DarkArea *screen;
};

class DarkArea : public QLabel
{
    Q_OBJECT
public:
    DarkArea(QWidget *parent);

    void show();

    void updateToolsBarPos();


    void moveToolBarLeftUp(); // перемещают toolBar слева/вверху/справа/внизу и внутри/снаружи ScreenShotArea
    void moveToolBarLeftDown();
    void moveToolBarUpLeft();
    void moveToolBarUpRight();
    void moveToolBarRightUp();
    void moveToolBarRightDown();
    void moveToolBarDownLeft();
    void moveToolBarDownRight();

    const QGroupBox *getGb_1() const { return gb_1; }
    const QGroupBox *getGb_2() const { return gb_2; }
    const QGroupBox *getGb_3() const { return gb_3; }
    const QGroupBox *getGb_4() const { return gb_4; }

private slots:
    void resizeEvent(QResizeEvent *e) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    void expScreenArea(QMouseEvent *e);
    void expScreenAreaLeft(QMouseEvent *e);              // изменяют размеры gb_ согласно позиции мыши
    void expScreenAreaRight(QMouseEvent *e);            // оставляют не затемненную зону для ScreenShotArea
    void expScreenAreaUp(QMouseEvent *e);
    void expScreenAreaDown(QMouseEvent *e);

    QGroupBox *gb_1; // создают затемнённую область
    QGroupBox *gb_2;
    QGroupBox *gb_3;
    QGroupBox *gb_4;

    ScreenShotArea *SSArea;
    ToolBar *toolBar;

    QPoint prevMousePos;

    int tbIndent = 10; // отступ toolBar от ScreenShotArea
    bool tbInside = false; // будет распологаться toolbar внутри или снаружи ScreenShotArea

// Отвечают, какой параметр будет изменяться у ScreenShotArea при перемещении мыши
    bool changeY; // true - менятся позиция по y, false - меняться height
    bool changeX; // true - менятся позиция по x, false - меняться width

    const quint8 GB_OPACITY = 100; // прозрачность затемнения 0 - 255
};

class ScreenShotArea : public QGroupBox
{
    Q_OBJECT
public:
    ScreenShotArea(DarkArea *sa);


private slots:
    void resizeEvent(QResizeEvent *e) override;

private:
    DarkArea *parent;
};

class ToolBar : public QGroupBox
{
    Q_OBJECT
public:
    ToolBar(DarkArea *parent);


    void setVertical(); // вертикальное/горизонтальное расположение
    void setHorizontal();

    void rotate();

private slots:
    void resizeEvent(QResizeEvent *e) override;

private:
    DarkArea *parent;
    QPushButton *btn1;
    QPushButton *btn2;

    bool isVertical = true; // true - вертикально расположен, false - горизонтально
};

#endif // SCREENSHOTMAKER_H
