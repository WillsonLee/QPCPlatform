//添加头文件路径
INCLUDEPATH += /usr/include/eigen3		//Eigen
INCLUDEPATH += /usr/local/include		//boost
INCLUDEPATH += /usr/local/include/vtk-7.1       //vtk
//INCLUDEPATH += /usr/include			//flann,this path should not be added,lest it cause error
INCLUDEPATH += /usr/local/include/pcl-1.10
//添加需要链接的库
LIBS += /usr/lib/x86_64-linux-gnu/libflann*.so
LIBS += /usr/local/lib/libboost_*.so
LIBS += /usr/local/lib/libvtk*.so
LIBS += /usr/local/lib/libpcl_*.so
