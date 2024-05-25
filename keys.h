#ifndef KEYS_H
#define KEYS_H

#include "menu.h"
#include <QString>
#include <map>
#include <list>

/* KeyShortcut хранит последовательность клавиш
 * Eсли все клавиши из этой последовательности нажаты - вызывает заданную функцию
 * Необходимо через Qtшный класс, используя keyPressEvent и keyReleaseEvent,
 * вызывать keyPress и keyRelease соответственно
 * Может работать только с MainWidget (мне впадлу писать шаблон, я его написал только для это класса)
*/
class KeyShortcut
{
public:
    KeyShortcut() = default;
    KeyShortcut(Qt::Key key);
    KeyShortcut(const std::initializer_list<Qt::Key> &key);

    KeyShortcut &operator = (const KeyShortcut &ks);
    KeyShortcut &operator += (const KeyShortcut &ks);

    void setFunc(MainWidget *obj, void (MainWidget::*foo) ()) { func = foo; funcObj = obj; }

    void addKey(Qt::Key key);                             // добавляет один key
    void clear() { keys.clear(); }                        // удаляет все ключи

    void keyPress(Qt::Key key);                           // должен срабатывать, когда нажимается какая-либо клавиша
    void keyRelease(Qt::Key key);                         // должен срабатывать, когда отжимается какая-либо клавиша

    bool empty() const { return keys.empty(); }
    int  size()  const { return keys.size(); }

    std::list<Qt::Key> shortcut() const; // вернет список клавиш

    const std::map<Qt::Key, bool> getKeys() const { return keys; }

private:
    void releaseKeys();                         // всем кнопкам присваивает false

    std::map<Qt::Key, bool> keys;               // int: Qt::Key... , bool: true - клавиша нажата
    void (MainWidget::*func)()  = nullptr;
    MainWidget *funcObj = nullptr;
};

// Unicode Basic Latin block
const keyMap basicKeys =
{
    {Qt::Key_Space,    "Space"},
    {Qt::Key_Exclam,   "Exclam"},
    {Qt::Key_QuoteDbl, "QuoteDbl"},
    {Qt::Key_NumberSign, "NumberSign"},
    {Qt::Key_Dollar,  "Dollar"},
    {Qt::Key_Percent, "Percent"},
    {Qt::Key_Ampersand,  "Ampersand"},
    {Qt::Key_Apostrophe, "Apostrophe"},
    {Qt::Key_ParenLeft,  "ParenLeft"},
    {Qt::Key_ParenRight, "ParenRight"},
    {Qt::Key_Asterisk, "Asterisk"},
    {Qt::Key_Plus,   "Plus"},
    {Qt::Key_Comma,  "Comma"},
    {Qt::Key_Minus,  "Minus"},
    {Qt::Key_Period, "Period"},
    {Qt::Key_Slash,  "Slash"},
    {Qt::Key_0, "0"},
    {Qt::Key_1, "1"},
    {Qt::Key_2, "2"},
    {Qt::Key_3, "3"},
    {Qt::Key_4, "4"},
    {Qt::Key_5, "5"},
    {Qt::Key_6, "6"},
    {Qt::Key_7, "7"},
    {Qt::Key_8, "8"},
    {Qt::Key_9, "9"},
    {Qt::Key_Colon,     "Colon"},
    {Qt::Key_Semicolon, "Semicolon"},
    {Qt::Key_Less,  "Less"},
    {Qt::Key_Equal, "Equal"},
    {Qt::Key_Greater,  "Greater"},
    {Qt::Key_Question, "Question"},
    {Qt::Key_At, "At"},
    {Qt::Key_A, "A"},
    {Qt::Key_B, "B"},
    {Qt::Key_C, "C"},
    {Qt::Key_D, "D"},
    {Qt::Key_E, "E"},
    {Qt::Key_F, "F"},
    {Qt::Key_G, "G"},
    {Qt::Key_H, "H"},
    {Qt::Key_I, "I"},
    {Qt::Key_J, "J"},
    {Qt::Key_K, "K"},
    {Qt::Key_L, "L"},
    {Qt::Key_M, "M"},
    {Qt::Key_N, "N"},
    {Qt::Key_O, "O"},
    {Qt::Key_P, "P"},
    {Qt::Key_Q, "Q"},
    {Qt::Key_R, "R"},
    {Qt::Key_S, "S"},
    {Qt::Key_T, "T"},
    {Qt::Key_U, "U"},
    {Qt::Key_V, "V"},
    {Qt::Key_W, "W"},
    {Qt::Key_X, "X"},
    {Qt::Key_Y, "Y"},
    {Qt::Key_Z, "Z"},
    {Qt::Key_BracketLeft,  "BracketLeft"},
    {Qt::Key_Backslash,    "Backslash"},
    {Qt::Key_BracketRight, "BracketRight"},
    {Qt::Key_AsciiCircum, "AsciiCircum"},
    {Qt::Key_Underscore,  "Underscore"},
    {Qt::Key_QuoteLeft, "QuoteLeft"},
    {Qt::Key_BraceLeft, "BraceLeft"},
    {Qt::Key_Bar, "Bar"},
    {Qt::Key_BraceRight, "BraceRight"},
    {Qt::Key_AsciiTilde, "AsciiTilde"}
};

const keyMap miscKeys =
{
    {Qt::Key_Escape, "Escape"},
    {Qt::Key_Tab, "Tab"},
    {Qt::Key_Backtab, "Backtab"},
    {Qt::Key_Backspace, "Backspace"},
    {Qt::Key_Return, "Enter"},
    {Qt::Key_Enter, "Enter"},
    {Qt::Key_Insert, "Insert"},
    {Qt::Key_Delete, "Delete"},
    {Qt::Key_Pause, "Pause"},
    {Qt::Key_Print, "PrintScr"},
    {Qt::Key_SysReq, "SysReq"}
};

const keyMap cursorMoveKeys =
{
    {Qt::Key_Home, "Home"},
    {Qt::Key_End, "End"},
    {Qt::Key_Left, "Left"},
    {Qt::Key_Up, "Up"},
    {Qt::Key_Right, "Right"},
    {Qt::Key_Down, "Down"},
    {Qt::Key_PageUp, "PageUp"},
    {Qt::Key_PageDown, "PageDown"}
};

const keyMap modKeys =
{
    {Qt::Key_Shift, "Shift"},
    {Qt::Key_Control, "Ctrl"},
    {Qt::Key_Meta, "Meta"},
    {Qt::Key_Alt, "Alt"},
    {Qt::Key_CapsLock, "CapsLock"},
    {Qt::Key_NumLock, "NumLock"},
    {Qt::Key_ScrollLock, "ScrollLock"}
};

// F1 - F12
const keyMap funcKeys =
{
    {Qt::Key_F1, "F1"},
    {Qt::Key_F2, "F2"},
    {Qt::Key_F3, "F3"},
    {Qt::Key_F4, "F4"},
    {Qt::Key_F5, "F5"},
    {Qt::Key_F6, "F6"},
    {Qt::Key_F7, "F7"},
    {Qt::Key_F8, "F8"},
    {Qt::Key_F9, "F9"},
    {Qt::Key_F10, "F10"},
    {Qt::Key_F11, "F11"},
    {Qt::Key_F12, "F12"},
};

inline KeyPair keyToKeyPair(int key)
{
    KeyPair pair;
    if(key >= 0x20 && key <= 0x7e) {
        pair = *(basicKeys.find(key));
    }
    else if(key >= 0x01000000 && key <= 0x0100000a) {
        pair = *(miscKeys.find(key));
    }
    else if(key >= 0x01000010 && key <= 0x01000017) {
        pair = *(cursorMoveKeys.find(key));
    }
    else if(key >= 0x01000020 && key <=  0x01000025) {
        pair = *(modKeys.find(key));
    }
    else if(key >= 0x01000030 && key <=  0x0100003b) {
        pair = *(funcKeys.find(key));
    }
    else return KeyPair(-1, "NULL");
    return pair;
}

#endif // KEYS_H
