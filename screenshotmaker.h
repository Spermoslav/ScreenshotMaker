#ifndef SCREENSHOTMAKER_H
#define SCREENSHOTMAKER_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>

#include "pin.h"

class MainWidget;
class Screen;
class ScreenShotArea;   // зона скриншота
class ToolBar;          // инструменты для взаимодействия с ScreenShotArea
class ShowRect;         // выводит размеры виджета "width() x height()"

class ScreenShotMaker : public QWidget
{
public:
    ScreenShotMaker(MainWidget *menu);

    void activate();

    void makeScreenShot(const QString &dir = "NULL");

    void close();

    void reset();

private:
    Screen *screen;

    MainWidget *menu;
};

class Screen : public QLabel
{
    Q_OBJECT
public:
    Screen(ScreenShotMaker *parent);

    void reset();

    void updateToolsBarPos();
    void updateSSAreaRectPos();

    QPixmap grabScreenShotArea();

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
    void closePBClicked();

private:
    Screen *parent;
    ScreenShotMaker *SSMaker;

    QPushButton *fastSavePB;
    QPushButton *savePB;
    QPushButton *closePB;

    bool isVertical = true; // true - вертикально расположен, false - горизонтально
};

// Отображает размеры заданного виджета
class ShowRect : public QLabel
{
public:
    ShowRect(QWidget *parent, const QWidget *obj);
    void update();              // обновляет текст согласно размерам виджета
    void updateWidth();         // обновляет свой размер под размеры текста
private:
    QWidget *parent;
    const QWidget *obj;         // объект, размеры которого отображает
};

#endif // SCREENSHOTMAKER_H
