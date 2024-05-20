#include "keys.h"
#include <QDebug>

KeyShortcut::KeyShortcut(const std::initializer_list<Qt::Key> &key)
{
    for(auto k : key) {
        keys.emplace(k, false);
    }
    for(auto k : keys) {
        qDebug() << k;
    }
}

KeyShortcut::KeyShortcut(Qt::Key key)
{
    keys.emplace(key, false);
}


KeyShortcut &KeyShortcut::operator =(const KeyShortcut &ks)
{
    keys = ks.keys;
    return *this;
}

KeyShortcut &KeyShortcut::operator +=(const KeyShortcut &ks)
{
    for(auto k : ks.keys) {
        if(keys.find(k.first) == keys.end()) {
            keys.emplace(k);
        }
    }
    return *this;
}

void KeyShortcut::addKey(Qt::Key key)
{
    keys.emplace(key, false);
}

void KeyShortcut::keyPress(Qt::Key key)
{
    if(func){
        bool allPress = false;
        (*keys.find(key)).second = true;             // кнопке, которую нажали присваеваем true

        for(auto &m : keys) {
            if(m.second == true) allPress = true;    // проверяем, все ли кнопки из мапы нажаты
            else {
                allPress = false;
                break;
            }
        }

        if(allPress) (funcObj->*func)();
    }
    else {
        qDebug() << "KeyShortcut::func == nullptr";
    }
}

void KeyShortcut::keyRelease(Qt::Key key)
{
    if(func) {
        for(auto &k : keys) {
            if(k.first == key) k.second = false;      // кнопке, которую отжали присваеваем false
        }
    }
    else {
        qDebug() << "KeyShortcut::func == nullptr";
    }
}

std::list<Qt::Key> KeyShortcut::shortcut() const
{
    std::list<Qt::Key> key;
    for(auto &k : keys) {
        key.push_back(k.first);
    }
    return key;
}
