#ifndef LOOPCONTROL_H
#define LOOPCONTROL_H

#include "loopcontrol_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <loopcontrolwidget.h>

class LOOPCONTROLSHARED_EXPORT LoopControl:public IPlugin
{
public:
    LoopControl();

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
    LoopControlWidget *pluginWidget;
    bool running;
    int currentCount;
    int totalCount;

	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(LoopControl)
};
REGISTER_REFLEX(LoopControl)

#endif // TESTPLUGIN_H
