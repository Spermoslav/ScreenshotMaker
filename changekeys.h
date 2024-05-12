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
    void keyPressEvent(QKeyEvent *e)   override;
    void keyReleaseEvent(QKeyEvent *e) override;

    void savePBClicked();
    void cancelPBClicked();

private:
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
