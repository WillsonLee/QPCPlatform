#ifndef THREEDTOMAT_H
#define THREEDTOMAT_H

#include "threedtomat_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <threedtomatwidget.h>

class THREEDTOMATSHARED_EXPORT ThreeDToMat:public IPlugin
{
public:
    ThreeDToMat();

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
    ThreeDToMatWidget *pluginWidget;
    double GSD;
    int mode;
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(ThreeDToMat)
};
REGISTER_REFLEX(ThreeDToMat)

#endif // TESTPLUGIN_H
