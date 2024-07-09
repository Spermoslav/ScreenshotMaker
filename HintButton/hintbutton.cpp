#include "hintbutton.h"
#include <QApplication>

HintButton::HintButton(QWidget *btnpar, QWidget* hintpar)
    : QPushButton(btnpar)
{
    hintL = new QLabel("hint", hintpar, Qt::FramelessWindowHint);
    hintL->hide();

    showHintTimer = new QTimer(this);
    showHintTimer->setInterval(500);
    connect(showHintTimer, &QTimer::timeout, this, &HintButton::showHint);

    setMouseTracking(true);
    installEventFilter(this);
}

HintButton::HintButton(const QString &text, QWidget *btnpar, QWidget* hintpar)
    : QPushButton(text, btnpar)
{
    hintL = new QLabel("hint", hintpar, Qt::FramelessWindowHint);
    hintL->hide();

    showHintTimer = new QTimer(this);
    showHintTimer->setInterval(500);
    connect(showHintTimer, &QTimer::timeout, this, &HintButton::showHint);

    setMouseTracking(true);
    installEventFilter(this);
}

HintButton::HintButton(const QString &text, const QString &hint, QWidget *btnpar, QWidget *hintpar)
    : QPushButton(text, btnpar)
{
    hintL = new QLabel(hint, hintpar, Qt::FramelessWindowHint);
    hintL->hide();

    showHintTimer = new QTimer(this);
    showHintTimer->setInterval(500);
    connect(showHintTimer, &QTimer::timeout, this, &HintButton::showHint);

    setMouseTracking(true);
    installEventFilter(this);
}

void HintButton::setHint(const QString &hint)
{
    hintL->setText(hint);
}

void HintButton::setHintParent(QWidget *parent)
{
    hintL->setParent(parent);
}

void HintButton::setInterval(uint time)
{
    showHintTimer->setInterval(time);
}

void HintButton::setHintIndent(int ind)
{
    hintIndent = ind;
}

void HintButton::setHintContentsMargins(int left, int top, int right, int down)
{
    hintL->setContentsMargins(left, top, right, down);
}

void HintButton::setHintStyleSheet(const QString &style)
{
    hintL->setStyleSheet(style);
}

void HintButton::mouseMoveEvent(QMouseEvent *e)
{
    hintL->hide();
    showHintTimer->start();
}

bool HintButton::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this) {
        QEvent::Type type = event->type();
        if  (type == QEvent::Enter) {
            cursorIn = true;
        }
        else if (type == QEvent::Leave) {
            cursorIn = false;
        }
    }
    return QWidget::eventFilter(obj, event);
}

void HintButton::showHint()
{
    if(cursorIn) {
        moveHint();
        hintL->show();
    }
    showHintTimer->stop();
}

bool HintButton::checkLeft()
{
    const int indent = cursor().pos().x() - hintL->width() - hintIndent;

    if(hintL->parentWidget())
        return indent >= hintL->parentWidget()->x();
    else
        return indent >= 0;
}

bool HintButton::checkUp()
{
    const int indent = cursor().pos().y() - hintL->height() - hintIndent;

    if(hintL->parentWidget())
        return indent >= hintL->parentWidget()->y();
    else
        return indent >= 0;
}

bool HintButton::checkRight()
{
    const int indent = cursor().pos().x() + hintL->width() + hintIndent;

    if(hintL->parentWidget())
        return indent <= hintL->parentWidget()->width();
    else
        return indent <= QApplication::primaryScreen()->size().width();
}

bool HintButton::checkDown()
{
    const int indent = cursor().pos().y() + 30 + hintL->height() + hintIndent;

    if(hintL->parentWidget())
        return indent <= hintL->parentWidget()->height();
    else
        return indent <= QApplication::primaryScreen()->size().height();
}

void HintButton::moveHintLeft()
{
    hintL->move(QPoint(cursor().pos().x() - hintL->width() - hintIndent, hintL->y()));
}

void HintButton::moveHintUp()
{
   hintL->move(QPoint(hintL->x(), cursor().pos().y() - hintL->height() - hintIndent));
}

void HintButton::moveHintRight()
{
    hintL->move(QPoint(cursor().pos().x() + hintIndent, hintL->y()));
}

void HintButton::moveHintDown()
{
    hintL->move(QPoint(hintL->x(), cursor().pos().y() + 30 + hintIndent));
}

void HintButton::moveHint()
{
    if(checkUp()){
        moveHintUp();
        if(checkRight())
            moveHintRight();
        else
            moveHintLeft();
    }
    else{
        moveHintDown();
        if(checkRight())
            moveHintRight();
        else
            moveHintLeft();
    }
}
