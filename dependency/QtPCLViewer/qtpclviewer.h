#ifndef QTPCLVIEWER_H
#define QTPCLVIEWER_H

#include "qtpclviewer_global.h"
#include <Any.h>
#include <pcdisplaythread.h>

class QTPCLVIEWERSHARED_EXPORT QtPCLViewer
{

public:
    QtPCLViewer();
    static bool showPointCloud(Any pcHolder);
    static void terminateAllDisplay();
private:
    static PCDisplayThread display;
};

#endif // QTPCLVIEWER_H
