#-------------------------------------------------
#
# Project created by QtCreator 2019-09-08T21:45:00
#
#-------------------------------------------------

QT       -= gui

TARGET = TestPlugin
TEMPLATE = lib

DEFINES += TESTPLUGIN_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += testplugin.cpp \
    testwidget.cpp

HEADERS += testplugin.h\
        testplugin_global.h \
    testwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


INCLUDEPATH +=../QPCPlatform/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../Reflex/release/ -lReflex
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../Reflex/debug/ -lReflex
else:unix: LIBS += -L$$PWD/../Reflex/ -lReflex

INCLUDEPATH += $$PWD/../Reflex
DEPENDPATH += $$PWD/../Reflex/release

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../IPlugin/release/ -lIPlugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../IPlugin/debug/ -lIPlugin
else:unix: LIBS += -L$$PWD/../IPlugin/ -lIPlugin

INCLUDEPATH += $$PWD/../IPlugin
DEPENDPATH += $$PWD/../IPlugin/release

FORMS += \
    testwidget.ui

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
