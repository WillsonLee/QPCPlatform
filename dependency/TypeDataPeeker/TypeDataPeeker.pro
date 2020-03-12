#-------------------------------------------------
#
# Project created by QtCreator 2019-09-20T11:26:30
#
#-------------------------------------------------

QT       -= gui

TARGET = TypeDataPeeker
TEMPLATE = lib

DEFINES += TYPEDATAPEEKER_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += typedatapeeker.cpp

HEADERS += typedatapeeker.h\
        typedatapeeker_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../../include

# copy header to QPCPlatform/include
win32 {
    system(copy typedatapeeker_global.h ..\\..\\include\\typedatapeeker_global.h)
    system(copy typedatapeeker.h ..\\..\\include\\typedatapeeker.h)
}
unix {
    system(cp typedatapeeker_global.h ../../include/typedatapeeker_global.h)
    system(cp typedatapeeker.h ../../include/typedatapeeker.h)
}
DESTDIR = $$PWD/../../lib
