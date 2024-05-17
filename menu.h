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

class MainWidget;
class ChangeKeys;
class ScreenShotMaker;

class FileConfig // хранит настройки файла
{
    friend MainWidget;
public:
    const static QString &dir() { return DIR; }
    const static QString &fileExt() { return EXT; }

    const static inline QString EXT_LIST = "PNG (*.png);; JPEG (*.jpeg);"; // список расширений скриншота для QFileDialog::getSaveFileName
private:
    static inline QString DIR = "C:/Users/Лёня/Рабочий стол/"; // директория для файла
    static inline QString EXT = ".png";                        // расширение для файла
};

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void setKey(const std::list<KeyPair> &keys);
    void updateKeysLabel();

    FileConfig fileDir;

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

    ChangeKeys *changeKeys;
    const static inline QString dirLabelStr = "Путь по умолчанию: ";
    const static inline QString fileExtStr  = "Расширение файла: ";
};



#endif // WIDGET_H
