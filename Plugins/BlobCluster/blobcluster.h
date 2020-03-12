#ifndef BLOBCLUSTER_H
#define BLOBCLUSTER_H

#include "blobcluster_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <blobclusterwidget.h>

class BLOBCLUSTERSHARED_EXPORT BlobCluster:public IPlugin
{
public:
    BlobCluster();

    // IPlugin interface
public:
    int getInputCount();
    std::vector<std::string> getInputTypes();
    int getOutputCount();
    std::vector<std::string> getOutputTypes();
    void run();
    void cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets);
    QWidget *getWidget();
    std::string saveState();
    bool restoreState(std::string stateFile);
    std::string getDoc();
    std::vector<std::string> getInputInfo();
    std::vector<std::string> getOutputInfo();
private:
    //定义内部参数
    BlobClusterWidget *pluginWidget;
    bool fourNeighbors;
    int outType;
    bool removal;
    int area;
    std::vector<int> types;
    int algoIndex;
    std::vector<int> algorithms;
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(BlobCluster)
};
REGISTER_REFLEX(BlobCluster)

#endif // TESTPLUGIN_H
