#ifndef PLOTTER2D_H
#define PLOTTER2D_H

#include "plotter2d_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <plotter2dwidget.h>
#include <QVector>

class PLOTTER2DSHARED_EXPORT Plotter2D:public IPlugin
{
public:
    Plotter2D();

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
    Plotter2DWidget *pluginWidget;
    SignalDelegate messenger;
    void getInputs(QVector<double> &x,QVector<double> &y);
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(Plotter2D)
};
REGISTER_REFLEX(Plotter2D)

#endif // TESTPLUGIN_H
