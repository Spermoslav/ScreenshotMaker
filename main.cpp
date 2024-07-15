#include "menu.h"
#include "keyboardhook.h"

#include <QApplication>
#include <QSharedMemory>

extern HHOOK hook;

int main(int argc, char *argv[])
{
    QSharedMemory global("key");
    if (!global.create(1)) // если другой процесс уже создал разделяемую память то выходим
        return 1;

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
