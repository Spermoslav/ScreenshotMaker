#include "keys.h"
#include <QDebug>

KeyShortcut::KeyShortcut(const std::initializer_list<Qt::Key> &key)
{
    for(Qt::Key k : key) {
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
