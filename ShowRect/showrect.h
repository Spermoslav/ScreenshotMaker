#ifndef SHOWRECT_H
#define SHOWRECT_H

#include <QWidget>
#include <QLabel>

// Отображает размеры заданного виджета
class ShowRect : public QLabel
{
public:
    explicit ShowRect(const QWidget *obj, QWidget *parent = nullptr);
    void update();              // обновляет текст согласно размерам виджета
    void updateWidth();         // обновляет свой размер под размеры текста
private:
    const QWidget *obj;         // объект, размеры которого отображает
};

#endif // SHOWRECT_H
