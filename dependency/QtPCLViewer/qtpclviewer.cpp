#include "qtpclviewer.h"
#include <stdexcept>

PCDisplayThread QtPCLViewer::display;

QtPCLViewer::QtPCLViewer()
{
}

bool QtPCLViewer::showPointCloud(Any pcHolder)
{
    if(!pcHolder.isNull()){
        terminateAllDisplay();
        display.setCloud(pcHolder);
        try{
            display.start();
        }
        catch(std::exception e){
            throw e;
        }
        catch(...){
            std::logic_error ee("unknown exception occurred when try to display (vector of) point cloud!");
            throw std::exception(ee);
        }
        return true;
    }
    return false;
}

void QtPCLViewer::terminateAllDisplay()
{
    if(display.isRunning()){
        display.terminate();
    }
}
