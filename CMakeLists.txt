cmake_minimum_required(VERSION 3.5)

project(ScreenshotMaker VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        defines.h
        KeyBoardHook/keyboardhook.h
        KeyBoardHook/keyboardhook.cpp
        SSMaker/screenshotmaker.h
        SSMaker/screenshotmaker.cpp
        ShowRect/showrect.h
        ShowRect/showrect.cpp
        menu/changekeys.h
        menu/changekeys.cpp
        keys/keys.h
        keys/keys.cpp
        keys/KeyShortcut.h
        menu/menu.h
        menu/menu.cpp
        pin/pin.h
        pin/pin.cpp
        HintButton/hintbutton.h
        HintButton/hintbutton.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ScreenshotMaker
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ScreenshotMaker APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ScreenshotMaker SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ScreenshotMaker
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ScreenshotMaker PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(ScreenshotMaker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(
    ShowRect
    SSMaker
    pin
    KeyBoardHook
    keys
    menu
    HintButton
)

set_target_properties(ScreenshotMaker PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ScreenshotMaker
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ScreenshotMaker)
endif()
