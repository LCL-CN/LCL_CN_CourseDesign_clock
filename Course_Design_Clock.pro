QT       += core gui
QT       +=multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    countdown_timer.cpp \
    digital_clock.cpp \
    forward_timer.cpp \
    main.cpp \
    dialog.cpp \
    pointer_clock.cpp

HEADERS += \
    countdown_timer.h \
    dialog.h \
    digital_clock.h \
    forward_timer.h \
    pointer_clock.h

FORMS += \
    dialog.ui

TRANSLATIONS += \
    Course_Design_Clock_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Sourse.qrc
