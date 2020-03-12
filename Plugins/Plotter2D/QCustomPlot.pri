win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../ProgramFiles/Qt/Qt5.8.0x86/5.8/msvc2015/lib/ -lQt5PrintSupport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../ProgramFiles/Qt/Qt5.8.0x86/5.8/msvc2015/lib/ -lQt5PrintSupportd
else:unix: LIBS += -L$$PWD/../../../ProgramFiles/Qt/Qt5.8.0x86/5.8/msvc2015/lib/ -lQt5PrintSupport

INCLUDEPATH += $$PWD/../../../ProgramFiles/Qt/Qt5.8.0x86/5.8/msvc2015/include
DEPENDPATH += $$PWD/../../../ProgramFiles/Qt/Qt5.8.0x86/5.8/msvc2015/include
