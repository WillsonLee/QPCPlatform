#-------------------------------------------------
#
# Project created by QtCreator 2019-09-25T15:37:26
#
#-------------------------------------------------

QT       += widgets

TARGET = QtPCLViewer
TEMPLATE = lib

DEFINES += QTPCLVIEWER_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += qtpclviewer.cpp \
    pcdisplaythread.cpp

HEADERS += qtpclviewer.h\
        qtpclviewer_global.h \
    pcdisplaythread.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    PCL.pri
include(PCL.pri)

INCLUDEPATH +=  $$PWD/../../include

# copy header to QPCPlatform/include
win32 {
    system(copy qtpclviewer_global.h ..\\..\\include\\qtpclviewer_global.h)
    system(copy qtpclviewer.h ..\\..\\include\\qtpclviewer.h)
    system(copy pcdisplaythread.h ..\\..\\include\\pcdisplaythread.h)
}
unix {
    system(cp qtpclviewer_global.h ../../include/qtpclviewer_global.h)
    system(cp qtpclviewer.h ../../include/qtpclviewer.h)
    system(cp pcdisplaythread.h ../../include/pcdisplaythread.h)
}
DESTDIR = $$PWD/../../lib
