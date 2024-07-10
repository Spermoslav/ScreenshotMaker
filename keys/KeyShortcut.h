#ifndef KEYSHORTCUT_H
#define KEYSHORTCUT_H

#include <list>
#include "qnamespace.h"
#include "defines.h"

/* KeyShortcut хранит последовательность клавиш
 * Eсли все клавиши из этой последовательности нажаты - вызывает заданную функцию
 * Необходимо через Qtшный класс, используя keyPressEvent и keyReleaseEvent, вызывать keyPress и keyRelease соответственно
*/

template<typename T>
class KeyShortcut
{
public:
    KeyShortcut() = default;
    explicit KeyShortcut(Qt::Key key)
    {
        keys.push_back(KeyStatus(key, false));
    }
    explicit KeyShortcut(const std::initializer_list<Qt::Key> &key)
    {
        for(Qt::Key k : key) {
            if(std::find(keys.begin(), keys.end(), KeyStatus(k, false)) == keys.end())
                keys.push_back(KeyStatus(k, false));
        }
    }
    void clear() { keys.clear(); }                        // удаляет все ключи
    void setFunc(T *obj, void (T::*foo) ()) { func = foo; funcObj = obj; }
    bool empty() const { return keys.empty(); }
    int  size()  const { return keys.size(); }
    const std::list<KeyStatus> getKeys() const { return keys; }

    void addKey(Qt::Key key)                                // добавляет один key
    {
        if(std::find(keys.begin(), keys.end(), KeyStatus(key, false)) == keys.end())
            keys.push_back(KeyStatus(key, false));
    }

    void keyPress(Qt::Key key)                           // должен срабатывать, когда нажимается какая-либо клавиша
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
    }
    void keyRelease(Qt::Key key)                         // должен срабатывать, когда отжимается какая-либо клавиша
    {
        if(func) {
            for(KeyStatus &k : keys) {
                if(k.first == key) {
                    k.second = false;
                }
            }
        }
    }

    std::list<Qt::Key> shortcut() const                  // вернет список клавиш
    {
        std::list<Qt::Key> key;
        for(const KeyStatus &k : keys) {
            key.push_back(k.first);
        }
        return key;
    }

private:
    void releaseKeys()  // всем кнопкам присваивает false
    {
        for(KeyStatus &p : keys) {
            p.second = false;
        }
    }

    std::list<KeyStatus> keys;
    void (T::*func)()  = nullptr;
    T *funcObj = nullptr;
};

#endif // KEYSHORTCUT_H
