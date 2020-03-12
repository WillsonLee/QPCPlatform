#-------------------------------------------------
#
# Project created by QtCreator 2019-09-07T22:54:30
#
#-------------------------------------------------

QT       += core gui
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QPCPlatform
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    shell.cpp \
    flow.cpp \
    typenamedisplayer.cpp \
    intropagewidget.cpp \
    proppagewidget.cpp

HEADERS  += mainwindow.h \
    shell.h \
    flow.h \
    typenamedisplayer.h \
    intropagewidget.h \
    proppagewidget.h

FORMS    += mainwindow.ui \
    shell.ui \
    flow.ui \
    intropagewidget.ui \
    proppagewidget.ui

INCLUDEPATH +=$$PWD/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lReflex
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lReflex
else:unix: LIBS += -L$$PWD/lib/ -lReflex

win32 {
    INCLUDEPATH +=D:/PCL-1.8.1/3rdParty/Eigen/eigen3
}
unix {
    INCLUDEPATH += /usr/include/eigen3
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lTypeDataPeeker
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lTypeDataPeeker
else:unix: LIBS += -L$$PWD/lib/ -lTypeDataPeeker

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lIPlugin
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lIPlugin
else:unix: LIBS += -L$$PWD/lib/ -lIPlugin

DISTFILES += \
    OpenCV.pri

include(OpenCV.pri)

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lQtPCLViewer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lQtPCLViewer
else:unix: LIBS += -L$$PWD/lib/ -lQtPCLViewer