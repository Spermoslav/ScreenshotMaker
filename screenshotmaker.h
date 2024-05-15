#ifndef SCREENSHOTMAKER_H
#define SCREENSHOTMAKER_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QLabel>

class DarkArea;
class ScreenShotArea; // зона скриншота

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

    QPoint prevMousePos;
    const quint8 GB_OPACITY = 100; // прозрачность затемнения 0 - 255

// Отвечают, какой параметр будет изменяться у ScreenShowArea при перемещении мыши
    bool changeY; // true - менятся позиция по y, false - меняться height
    bool changeX; // true - менятся позиция по x, false - меняться width
};

class ScreenShotArea : public QGroupBox
{
    Q_OBJECT
public:
    ScreenShotArea(DarkArea *sa);


private slots:


private:
    DarkArea *parent;
};

#endif // SCREENSHOTMAKER_H
