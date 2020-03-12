#ifndef MINBOUNDINGBOX_H
#define MINBOUNDINGBOX_H

#include "minboundingbox_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <minboundingboxwidget.h>

class MINBOUNDINGBOXSHARED_EXPORT MinBoundingBox:public IPlugin
{
public:
    MinBoundingBox();

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
    MinBoundingBoxWidget *pluginWidget;
    bool binary;
    bool merge;
    int node;
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(MinBoundingBox)
};
REGISTER_REFLEX(MinBoundingBox)

#endif // TESTPLUGIN_H
