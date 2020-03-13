unix {
    # 添加eigen库和lyxutils库路径
    INCLUDEPATH += /usr/local/include/lyxutils
    INCLUDEPATH += /usr/include/eigen3
    LIBS    += -L/usr/local/lib/ -lutils
}
win32 {
    INCLUDEPATH +=D:\workdir\VisualStudio\Utilities\Utilities
    INCLUDEPATH +=D:\PCL-1.8.1\3rdParty\Eigen\eigen3
}
