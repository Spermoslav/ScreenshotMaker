#ifndef KEYS_H
#define KEYS_H

#include <QString>
#include <vector>

// Unicode Basic Latin block
const std::vector<QString> basicKeys =
{
    "Space",
    "Exclam",
    "QuoteDbl",
    "NumberSign",
    "Dollar",
    "Percent",
    "Ampersand",
    "Apostrophe",
    "ParenLeft",
    "ParenRight",
    "Asterisk",
    "Plus",
    "Comma",
    "Minus",
    "Period",
    "Slash",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "Colon",
    "Semicolon",
    "Less",
    "Equal",
    "Greater",
    "Question",
    "At",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "BracketLeft",
    "Backslash",
    "BracketRight",
    "AsciiCircum",
    "Underscore",
    "QuoteLeft",
    "BraceLeft",
    "Bar",
    "BraceRight",
    "AsciiTilde"
};

const std::vector<QString> miscKeys =
{
    "Escape",
    "Tab",
    "Backtab",
    "Backspace",
    "Enter",
    "Return",
    "Insert",
    "Delete",
    "Pause",
    "PrintScr",
    "SysReq"
};

const std::vector<QString> cursorMoveKeys =
{
    "Home",
    "End",
    "Left",
    "Up",
    "Right",
    "Down",
    "PageUp",
    "PageDown",
};

const std::vector<QString> modKeys =
{
    "Shift",
    "Control",
    "Meta",
    "Alt",
    "CapsLock",
    "NumLock",
    "ScrollLock",
};

// F1 - F12
const std::vector<QString> funcKeys =
{
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
};

static inline QString keyToString(int key)
{
    if(key >= 32 && key <= 126)
        return basicKeys[key - 0x01000010];
    else if(key >= 0x01000000 && key <= 0x0100000a) {
        return miscKeys[key - 0x01000000];
    }
    else if(key >= 0x01000010 && key <= 0x01000017) {
        return cursorMoveKeys[key - 0x01000010];
    }
    else if(key >= 0x01000020 && key <=  0x01000025) {
        return modKeys[key - 0x01000020];
    }
    else if(key >= 0x01000030 && key <=  0x0100003b) {
        return funcKeys[key - 0x01000030];
    }
    else return QString::number(key);
}

#endif // KEYS_H
