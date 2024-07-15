#include "menu.h"
#include "keyboardhook.h"

#include <QApplication>

extern HHOOK hook;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.setMinimumSize(250, 500);
    w.setGeometry(200, 200, 400, 650);
    w.setWindowFlag(Qt::Tool);
    w.show();
    QApplication::setQuitOnLastWindowClosed(false);

    hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallBack, NULL, 0);

    return a.exec();
}
