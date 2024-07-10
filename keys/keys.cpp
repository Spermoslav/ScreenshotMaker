#include "keys.h"
#include <QDebug>

KeyShortcut::KeyShortcut(const std::initializer_list<Qt::Key> &key)
{
    for(Qt::Key k : key) {
        if(std::find(keys.begin(), keys.end(), KeyStatus(k, false)) == keys.end())
            keys.push_back(KeyStatus(k, false));
    }
}

KeyShortcut::KeyShortcut(Qt::Key key)
{
    keys.push_back(KeyStatus(key, false));
}


KeyShortcut &KeyShortcut::operator =(const KeyShortcut &ks)
{
    keys = ks.keys;
    return *this;
}

KeyShortcut &KeyShortcut::operator +=(const KeyShortcut &ks)
{
    for(KeyStatus k : ks.keys) {
        if(std::find(keys.begin(), keys.end(), k) == keys.end()) {
            keys.push_back(k);
        }
    }
    return *this;
}

void KeyShortcut::addKey(Qt::Key key)
{
    if(std::find(keys.begin(), keys.end(), KeyStatus(key, false)) == keys.end())
        keys.push_back(KeyStatus(key, false));
}

void KeyShortcut::releaseKeys()
{
    for(KeyStatus &p : keys) {
        p.second = false;
    }
}

void KeyShortcut::keyPress(Qt::Key key)
{
    if(func){
        bool allPress = false;
        (*std::find(keys.begin(), keys.end(), KeyStatus(key, false))).second = true;  // кнопке, которую нажали присваеваем true

        for(const KeyStatus &m : keys) {
            if(m.second == true) allPress = true;                   // проверяем, все ли кнопки нажаты
            else {
                allPress = false;
                break;
            }
        }

        if(allPress) {                      // если все кнопки нажаты,
            releaseKeys();                  // присваиваем всем кнопкам false
            (funcObj->*func)();             // и вызываем функцию.
        }
    }
    else {
        qDebug() << "KeyShortcut::func == nullptr";
    }
}

void KeyShortcut::keyRelease(Qt::Key key)
{
    if(func) {
        for(KeyStatus &k : keys) {
            if(k.first == key) {
                k.second = false;      // кнопке, которую отжали присваеваем false
            }
        }
    }
    else {
        qDebug() << "KeyShortcut::func == nullptr";
    }
}

std::list<Qt::Key> KeyShortcut::shortcut() const
{
    std::list<Qt::Key> key;
    for(const KeyStatus &k : keys) {
        key.push_back(k.first);
    }
    return key;
}

Qt::Key winKeyToKey(int key)
{
    Qt::Key qKey;
    const int bn = 16777000;

    // отсортировал по частоте вхождения (на свой взгляд)
    if(key >= 112 && key <= 123) qKey = Qt::Key(key + bn + 152);   // F1 - F12
    else if(key == 44) qKey = Qt::Key_PrintScreen;
    else if(key == 162 || key == 163) qKey = Qt::Key_Control;
    else if(key == 164) qKey = Qt::Key_Alt;
    else if(key == 160 || key == 161) qKey = Qt::Key_Shift;
    else if(key == 27) qKey = Qt::Key::Key_Escape;
    else if(key >= 96 && key <= 105) qKey = Qt::Key(key - 48);     // NumPad 0 - 9
    else if(key == 35) qKey = Qt::Key_End;
    else if(key == 36) qKey = Qt::Key_Home;
    else if(key == 46) qKey = Qt::Key_Delete;
    else if(key == 33) qKey = Qt::Key_PageUp;
    else if(key == 34) qKey = Qt::Key_PageDown;
    else if(key >= 37 && key <= 40) qKey = Qt::Key(key + bn + 197); // left, up, right, down
    else if(key == 192) qKey = Qt::Key(96); // symbol `
    else if(key == 106) qKey = Qt::Key_Asterisk;
    else if(key == 107) qKey = Qt::Key_Plus;
    else if(key == 109 || key == 189) qKey = Qt::Key_Minus;
    else if(key == 111) qKey = Qt::Key_Backslash;
    else if(key == 187) qKey = Qt::Key_Equal;
    else if(key == 110) qKey = Qt::Key_Stop;
    else if(key == 13) qKey = Qt::Key_Enter;

    else qKey = Qt::Key(key);

    return qKey;
}
