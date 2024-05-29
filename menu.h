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
#include "defines.h"

class KeyShortcut;
class MainWidget;
class ChangeKeys;
class ScreenShotMaker;

using KeyPair = std::pair<int, QString>;
using keyMap  = std::map<int, QString>;

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

    void setKey(const std::list<KeyPair> &key);
    void updateKeysLabel();

    FileConfig fileDir;

private slots:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

    void keyShortcutPress();

    void fileExtActivated(int index);
    void dirPBClicked();
    void keyChangePBClicked();

private:
    ScreenShotMaker *SSMaker;

    KeyShortcut* keys;

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
