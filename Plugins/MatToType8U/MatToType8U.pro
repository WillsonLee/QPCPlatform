#-------------------------------------------------
#
# Project created by QPCPlatform 2019-09-24 09:25:23
#
#-------------------------------------------------

QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = MATTOTYPE8U
TEMPLATE = lib

DEFINES += MATTOTYPE8U_LIBRARY

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
    mattotype8u.cpp \
    

HEADERS += \
    mattotype8u.h \
    mattotype8u_global.h \
    

unix {
    target.path = /usr/lib
    INSTALLS += target
}


INCLUDEPATH +=D:/workdir/QPCPlatform/include

win32:CONFIG(release, debug|release): LIBS += -LD:/workdir/QPCPlatform/dependency/release/ -lReflex
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/workdir/QPCPlatform/dependency/debug/ -lReflex
else:unix: LIBS += -LD:/workdir/QPCPlatform/dependency/ -lReflex


win32:CONFIG(release, debug|release): LIBS += -LD:/workdir/QPCPlatform/dependency/release/ -lIPlugin
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/workdir/QPCPlatform/dependency/debug/ -lIPlugin
else:unix: LIBS += -LD:/workdir/QPCPlatform/dependency/ -lIPlugin



    

DISTFILES += \
    OpenCV.pri
include(OpenCV.pri)
