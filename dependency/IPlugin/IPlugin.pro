#-------------------------------------------------
#
# Project created by QtCreator 2019-09-08T15:47:02
#
#-------------------------------------------------

QT       += core gui
QT       += widgets

TARGET = IPlugin
TEMPLATE = lib

DEFINES += IPLUGIN_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += iplugin.cpp

HEADERS += iplugin.h\
        iplugin_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../../include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/ -lReflex
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/ -lReflex
else:unix: LIBS += -L$$PWD/../../lib/ -lReflex

# copy header to QPCPlatform/include
win32 {
    system(copy iplugin_global.h ..\\..\\include\\iplugin_global.h)
    system(copy iplugin.h ..\\..\\include\\iplugin.h)
}
unix {
    system(cp iplugin_global.h ../../include/iplugin_global.h)
    system(cp iplugin.h ../../include/iplugin.h)
}
DESTDIR = $$PWD/../../lib
