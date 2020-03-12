#ifndef GAMMATRANSFORM_H
#define GAMMATRANSFORM_H

#include "gammatransform_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <gammatransformwidget.h>
#include <opencv2/opencv.hpp>


class GAMMATRANSFORMSHARED_EXPORT GammaTransform:public IPlugin
{
public:
    GammaTransform();

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
    GammaTransformWidget *pluginWidget;
    cv::Mat table;
private:
    cv::Mat getLookUpTable(double gamma);
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(GammaTransform)
};
REGISTER_REFLEX(GammaTransform)

#endif // TESTPLUGIN_H
