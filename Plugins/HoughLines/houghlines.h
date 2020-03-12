#ifndef HOUGHLINES_H
#define HOUGHLINES_H

#include "houghlines_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <houghlineswidget.h>

class HOUGHLINESSHARED_EXPORT HoughLines:public IPlugin
{
public:
    HoughLines();

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
    HoughLinesWidget *pluginWidget;
    double rho;
    double theta;//in angle
    int threshold;
    double minLineLength;
    double maxGap;
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(HoughLines)
};
REGISTER_REFLEX(HoughLines)

#endif // TESTPLUGIN_H
