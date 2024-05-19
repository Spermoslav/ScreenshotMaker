#ifndef SCREENSHOTMAKER_H
#define SCREENSHOTMAKER_H

#include <QWidget>
#include <QGroupBox>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>

class MainWidget;
class Screen;
class ScreenShotArea; // зона скриншота
class ToolBar; // инструменты для взаимодействия с ScreenShotArea

class ScreenShotMaker : public QWidget
{
public:
    ScreenShotMaker(MainWidget *menu);

    void activate();

    void makeScreenShot(const QString &dir = "");

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

    void moveToolBarLeftUp(); // перемещают toolBar слева/вверху/справа/внизу и внутри/снаружи ScreenShotArea
    void moveToolBarLeftDown();
    void moveToolBarUpLeft();
    void moveToolBarUpRight();
    void moveToolBarRightUp();
    void moveToolBarRightDown();
    void moveToolBarDownLeft();
    void moveToolBarDownRight();

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

    int tbIndent = 10; // отступ toolBar от ScreenShotArea

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

    void makeScreenShot();

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

#endif // SCREENSHOTMAKER_H
