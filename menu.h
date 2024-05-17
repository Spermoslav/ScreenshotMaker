#ifndef WIDGET_H
#define WIDGET_H

#include <QString>
#include <QWidget>
#include <QKeyEvent>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QGroupBox>
#include <list>
#include "keys.h"

class ChangeKeys;
class ScreenShotMaker;

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void setKey(const std::list<KeyPair> &keys);
    void updateKeysLabel();

    const QString &getDir() const { return dir; }
    const QString &getFileExt() const { return fileExt; }

private slots:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

    void fileExtActivated(int index);
    void dirPBClicked();
    void keyChangePBClicked();

private:
    ScreenShotMaker *SSMaker;

    std::list<KeyPair> keys = {
                                {Qt::Key_Control, "Ctrl"},
                                {Qt::Key_Alt, "Alt"},
                                {Qt::Key_S, "S"}
                              };

    QLabel *dirLabel;
    QLabel *fileExtLabel;
    QLabel *keyLabel;

    QGroupBox *box;

    QPushButton *dirPB;
    QPushButton *keyChangePB;

    QComboBox *fileExtCB;

    QGridLayout *mainLay;

    QString dir     = "C:/Users/Лёня/Рабочий стол/";
    QString fileExt = ".png";

    ChangeKeys *changeKeys;
    const static inline QString dirLabelStr = "Путь по умолчанию: ";
    const static inline QString fileExtStr  = "Расширение файла: ";
};



#endif // WIDGET_H
