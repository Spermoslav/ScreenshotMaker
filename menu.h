#ifndef WIDGET_H
#define WIDGET_H

#include <QString>
#include <QWidget>
#include <QKeyEvent>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

    void fileExtActivated(int index);
    void dirPBClicked();

private:
    QLabel *dirLabel;
    QLabel *fileExtLabel;

    QPushButton *dirPB;

    QComboBox *fileExtCB;

    QGridLayout *mainLay;

    QString dir     = "C:/Users/Лёня/Рабочий стол";
    QString fileExt = ".png";

    QScreen *screen = nullptr;
    const static inline QString dirLabelStr = "Путь по умолчанию: ";
    const static inline QString fileExtStr  = "Расширение файла: ";
};
#endif // WIDGET_H
