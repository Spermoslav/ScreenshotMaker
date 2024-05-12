#ifndef WIDGET_H
#define WIDGET_H

#include <QString>
#include <QWidget>
#include <QKeyEvent>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <vector>



class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private slots:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

    void fileExtActivated(int index);
    void dirPBClicked();
    void keyChangePBClicked();

private:
    QLabel *dirLabel;
    QLabel *fileExtLabel;
    QLabel *keyLabel;

    QPushButton *dirPB;
    QPushButton *keyChangePB;

    QComboBox *fileExtCB;

    QGridLayout *mainLay;

    QString dir     = "C:/Users/Лёня/Рабочий стол";
    QString fileExt = ".png";

    QScreen *screen = nullptr;
    const static inline QString dirLabelStr = "Путь по умолчанию: ";
    const static inline QString fileExtStr  = "Расширение файла: ";
};

#endif // WIDGET_H
