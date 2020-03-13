#-------------------------------------------------
#
# Project created by QPCPlatform 2019-09-22 15:13:37
#
#-------------------------------------------------

QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = PCDLOADER
TEMPLATE = lib

DEFINES += PCDLOADER_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    pcdloader.cpp \
    pcdloaderwidget.cpp

HEADERS += \
    pcdloader.h \
    pcdloader_global.h \
    pcdloaderwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


INCLUDEPATH +=$$PWD/../../include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/ -lReflex
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/ -lReflex
else:unix: LIBS += -L$$PWD/../../lib/ -lReflex


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/ -lIPlugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/ -lIPlugin
else:unix: LIBS += -L$$PWD/../../lib/ -lIPlugin


CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../../plugins
}else{
    DESTDIR = $$PWD/../../plugins
}


FORMS += \
    pcdloaderwidget.ui

DISTFILES += \
    PCL.pri

include(PCL.pri)
