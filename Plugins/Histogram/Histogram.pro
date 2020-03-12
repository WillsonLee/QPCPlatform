#-------------------------------------------------
#
# Project created by QPCPlatform 2019-10-20 20:32:19
#
#-------------------------------------------------

QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = HISTOGRAM
TEMPLATE = lib

DEFINES += HISTOGRAM_LIBRARY

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
    histogram.cpp \
    histogramwidget.cpp

HEADERS += \
    histogram.h \
    histogram_global.h \
    histogramwidget.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


INCLUDEPATH +=D:/workdir/Qt/QPCPlatform/include

win32:CONFIG(release, debug|release): LIBS += -LD:/workdir/Qt/QPCPlatform/dependency/release/ -lReflex
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/workdir/Qt/QPCPlatform/dependency/debug/ -lReflex
else:unix: LIBS += -LD:/workdir/Qt/QPCPlatform/dependency/ -lReflex


win32:CONFIG(release, debug|release): LIBS += -LD:/workdir/Qt/QPCPlatform/dependency/release/ -lIPlugin
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/workdir/Qt/QPCPlatform/dependency/debug/ -lIPlugin
else:unix: LIBS += -LD:/workdir/Qt/QPCPlatform/dependency/ -lIPlugin


FORMS += \
    histogramwidget.ui

CONFIG(debug,debug|release){
    DESTDIR = D:/workdir/Qt/QPCPlatform/plugins
}else{
    DESTDIR = $$PWD/release
}

DISTFILES += \
    OpenCV.pri

include(OpenCV.pri)
