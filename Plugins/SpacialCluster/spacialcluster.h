#ifndef SPACIALCLUSTER_H
#define SPACIALCLUSTER_H

#include "spacialcluster_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <spacialclusterwidget.h>

class SPACIALCLUSTERSHARED_EXPORT SpacialCluster:public IPlugin
{
public:
    SpacialCluster();

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
    SpacialClusterWidget *pluginWidget;
    bool tolAuto;
    double tol;
    int min_pts;
    int max_pts;
    int xyz;//1表示XYZ型,2表示XYZRGB型,0表示没有需要清理的
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(SpacialCluster)
};
REGISTER_REFLEX(SpacialCluster)

#endif // TESTPLUGIN_H
