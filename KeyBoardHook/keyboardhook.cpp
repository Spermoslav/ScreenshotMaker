#include "keyboardhook.h"
#include "changekeys.h"

LRESULT HookCallBack(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0) {
        KeyStatus key;
        kbStruct = *((KBDLLHOOKSTRUCT*)lParam);

        if (wParam == WM_KEYDOWN) {
            key.second = true;
        }
        else if (wParam == WM_KEYUP) {
            key.second = false;
        }

        key.first = winKeyToKey(kbStruct.vkCode);

        if(Call::hookCKobj || Call::hookMWobj)
        {
            if(Call::hookCKobj->isActiveWindow())
            {
                if(Call::hookCKfunc)
                    (Call::hookCKobj->*Call::hookCKfunc)(key);

                else qDebug() << "Call::hookCKfunc is null";
            }
            else
            {
                if(Call::hookMWfunc)
                   (Call::hookMWobj->*Call::hookMWfunc)(key);

                else qDebug() << "Call::hookMWfunc is null";
            }
        }
        else qDebug() << "Call::hookCKobj || Call::hookMWobj is null";
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}
