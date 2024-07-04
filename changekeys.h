#ifndef CHANGEKEYS_H
#define CHANGEKEYS_H

#include <QWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <list>
#include "menu.h"
#include "keys.h"

class ChangeKeys : public QWidget
{
    Q_OBJECT
public:
    ChangeKeys(MainWidget *mw);

    void show();

private slots:
    void savePBClicked();
    void cancelPBClicked();

private:
    void keyEvent(KeyStatus ks);
    void keyPress(Qt::Key ks);
    void keyRelease();

    MainWidget *parent;

    QLabel *keysLabel;
    QPushButton *savePB;
    QPushButton *cancelPB;

    QVBoxLayout *main_lay;
    QHBoxLayout *btns_lay;

    std::list<KeyPair> keys;

    bool keysChanged = true;
};

#endif // CHANGEKEYS_H
