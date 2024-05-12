#include "changekeys.h"

ChangeKeys::ChangeKeys(MainWidget *mw)
    : QWidget()
{
    setWindowTitle("Нажмите нужные клавиши");

    parent = mw;

    keysLabel = new QLabel;
    keysLabel->setText("");
    keysLabel->setAlignment(Qt::AlignCenter);

    savePB = new QPushButton;
    savePB->setText("save");
    connect(savePB, &QPushButton::clicked, this, &ChangeKeys::savePBClicked);

    cancelPB = new QPushButton;
    cancelPB->setText("cancel");
    connect(cancelPB, &QPushButton::clicked, this, &ChangeKeys::cancelPBClicked);

    btns_lay = new QHBoxLayout;
    btns_lay->addWidget(savePB);
    btns_lay->addWidget(cancelPB);

    main_lay = new QVBoxLayout(this);
    main_lay->addWidget(keysLabel);
    main_lay->addLayout(btns_lay);
}

void ChangeKeys::show()
{
    static_cast<QWidget*> (this)->show();
    move(QCursor::pos());
    keys.clear();
}

void ChangeKeys::keyPressEvent(QKeyEvent *e)
{
    cancelPB->setText("cancel");
    if(keysChanged) {
        keysLabel->setText("");
        keys.clear();
        keysLabel->setText(keysLabel->text() + keyToKeyPair(e->key()).second);
        keys.push_back(keyToKeyPair(e->key()));
        keysChanged = false;
    }
    else {
        keysLabel->setText(keysLabel->text() + "+" + keyToKeyPair(e->key()).second);
        keys.push_back(keyToKeyPair(e->key()));
    }
}

void ChangeKeys::keyReleaseEvent(QKeyEvent *e)
{
    keysChanged = true;
}

void ChangeKeys::savePBClicked()
{
    parent->setKey(keys);
    cancelPB->setText("close");
}

void ChangeKeys::cancelPBClicked()
{
    keysLabel->setText("");
    keys.clear();
    keysChanged = true;
    hide();
}
