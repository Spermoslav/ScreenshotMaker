#include "keys.h"
#include <QDebug>





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
