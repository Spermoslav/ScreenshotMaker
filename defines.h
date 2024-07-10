#ifndef DEFINES_H
#define DEFINES_H

//#define DEBUG

#ifdef DEBUG
//    #define SSMAKER_WINDOW     // открывает меню скриншота в окне
    #define SSMAKER_START      // сразу запускает ScreenShotMaker
    #define SSMAKER_NOTTOPHINT // отключает размещение окна поверх всех
#endif // DEBUG

using KeyStatus = std::pair<Qt::Key, bool>; // true - кнопка нажата
using KeyPair = std::pair<int, QString>;
using keyMap  = std::map<int, QString>;

#endif // DEFINES_H
