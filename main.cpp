#include "menu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.setMinimumSize(250, 500);
    w.setGeometry(200, 200, 400, 650);
    w.show();
    return a.exec();
}
