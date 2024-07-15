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
#include <QStandardPaths>
#include <QFile>

#include "defines.h"
#include "keys.h"
#include "KeyShortcut.h"

class MainWidget;
class ChangeKeys;
class ScreenShotMaker;

class FileConfig // хранит настройки файла
{
    friend class MainWidget;
public:
    const static inline QString &dir() { return DIR; }
    const static inline QString &fileExt() { return EXT; }

    const static inline QString EXT_LIST = "PNG (*.png);; JPEG (*.jpeg);"; // список расширений скриншота для QFileDialog::getSaveFileName
    const static inline QString CONFIG_NAME = "config.cfg";

private:
    static inline QString DIR =             // директория для файла
QStandardPaths::standardLocations(QStandardPaths::DesktopLocation).join("/") + "/";

    static inline QString EXT = ".png";     // расширение для файла
};

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    void setKey(const std::list<KeyPair> &key);
    void updateKeysLabel();

    void close();

private slots:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

    void keyShortcutPress();

    void fileExtActivated(int index);
    void dirPBClicked();
    void keyChangePBClicked();

private:
    void keyEvent(KeyStatus ks);

    void updateConfig();

    ScreenShotMaker *SSMaker;

    KeyShortcut<MainWidget> keys;

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
