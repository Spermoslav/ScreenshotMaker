#ifndef KEYBOARDHOOK_H
#define KEYBOARDHOOK_H

#include "windows.h"
#include "menu.h"
#include <QDebug>

static HHOOK hook;

static KBDLLHOOKSTRUCT kbStruct;

// Срабатывает всякий раз, когда нажимается любая из клавиш на клавиатуре
// запускает keyPress методы у MainWidget/ChangeKeys класса
LRESULT CALLBACK HookCallBack(int nCode, WPARAM wParam, LPARAM lParam);

/* Хранит в себе статичные поля объекта и метода для MainWidget и ChangeKeys
 * Заданные функции запускает HookCallBack
 * По сути связывает нужный метод с HookCallBack
*/
class Call
{
    friend LRESULT CALLBACK HookCallBack(int nCode, WPARAM wParam, LPARAM lParam);
    friend MainWidget;
    friend ChangeKeys;

    static void setMenu(MainWidget* obj, void (MainWidget::*func)(KeyStatus))
    {
        hookMWobj = obj;
        hookMWfunc = func;
    }
    static void setChangeKeys(ChangeKeys* ck, void (ChangeKeys::*func)(KeyStatus))
    {
        hookCKobj = ck;
        hookCKfunc = func;
    }
    static inline MainWidget* hookMWobj = nullptr;
    static inline void (MainWidget::*hookMWfunc)(KeyStatus)  = nullptr;

    static inline ChangeKeys* hookCKobj = nullptr;
    static inline void (ChangeKeys::*hookCKfunc)(KeyStatus)  = nullptr;
};

#endif // KEYBOARDHOOK_H
