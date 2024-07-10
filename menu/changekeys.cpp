#include "changekeys.h"
#include "keyboardhook.h"

ChangeKeys::ChangeKeys(MainWidget *mw)
    : QWidget(),
      parent(mw),
      keysLabel(new QLabel),
      savePB(new QPushButton("save")),
      cancelPB(new QPushButton("cancel")),
      btns_lay(new QHBoxLayout),
      main_lay(new QVBoxLayout(this))
{
    setWindowTitle("Нажмите нужные клавиши");

    Call::setChangeKeys(this, keyEvent);

    keysLabel->setAlignment(Qt::AlignCenter);

    savePB->setText("save");
    cancelPB->setText("cancel");

    connect(savePB, &QPushButton::clicked, this, &ChangeKeys::savePBClicked);
    connect(cancelPB, &QPushButton::clicked, this, &ChangeKeys::cancelPBClicked);

    btns_lay->addWidget(savePB);
    btns_lay->addWidget(cancelPB);
    main_lay->addWidget(keysLabel);
    main_lay->addLayout(btns_lay);
}

void ChangeKeys::show()
{
    static_cast<QWidget*> (this)->show();
    move(QCursor::pos());
    keys.clear();
}

void ChangeKeys::savePBClicked()
{
    parent->setKey(keys);
    close();
}

void ChangeKeys::cancelPBClicked()
{
    keysLabel->setText("");
    keys.clear();
    keysChanged = true;
    hide();
}

void ChangeKeys::keyEvent(KeyStatus ks)
{
    if(ks.second) keyPress(ks.first);
    else keyRelease();
}

void ChangeKeys::keyPress(Qt::Key ks)
{
    savePB->setDisabled(true);
    cancelPB->setDisabled(true);

    KeyPair kp = keyToKeyPair(ks);

    if(keysChanged) {
        keysLabel->setText("");
        keys.clear();
        keysLabel->setText(keysLabel->text() + kp.second);
        keys.push_back(kp);
        keysChanged = false;
    }
    else {
        if(std::find(keys.begin(), keys.end(), kp) == keys.end()) {
            keysLabel->setText(keysLabel->text() + "+" + kp.second);
            keys.push_back(kp);
        }
    }
}

void ChangeKeys::keyRelease()
{
    keysChanged = true;
    savePB->setDisabled(false);
    cancelPB->setDisabled(false);
}
