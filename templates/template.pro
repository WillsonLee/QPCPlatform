#-------------------------------------------------
#
# Project created by QPCPlatform TIME_STAMP_AUTO_REPLACED
#
#-------------------------------------------------

QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = TARGET_NAME_AUTO_REPLACED
TEMPLATE = lib

DEFINES += TARGET_NAME_AUTO_REPLACED_LIBRARY

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
    FILE_NAME_AUTO_REPLACED.cpp \
    FILE_WIDGET_AUTO_REPLACED.cpp

HEADERS += \
    FILE_NAME_AUTO_REPLACED.h \
    FILE_NAME_AUTO_REPLACED_global.h \
    FILE_WIDGET_AUTO_REPLACED.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


INCLUDEPATH +=QPCPLATFORM_INCLUDEPATH_AUTO_REPLACED

win32:CONFIG(release, debug|release): LIBS += -LREFLEX_PATH_AUTO_REPLACED/release/ -lReflex
else:win32:CONFIG(debug, debug|release): LIBS += -LREFLEX_PATH_AUTO_REPLACED/debug/ -lReflex
else:unix: LIBS += -LREFLEX_PATH_AUTO_REPLACED/ -lReflex


win32:CONFIG(release, debug|release): LIBS += -LIPLUGIN_PATH_AUTO_REPLACED/release/ -lIPlugin
else:win32:CONFIG(debug, debug|release): LIBS += -LIPLUGIN_PATH_AUTO_REPLACED/debug/ -lIPlugin
else:unix: LIBS += -LIPLUGIN_PATH_AUTO_REPLACED/ -lIPlugin


FORMS += \
    FILE_WIDGET_AUTO_REPLACED.ui

CONFIG(debug,debug|release){
    DESTDIR = DEBUG_DLL_PATH_AUTO_REPLACED
}else{
    DESTDIR = RELEASE_DLL_PATH_AUTO_REPLACED
}