#ifndef MATLOADER_H
#define MATLOADER_H

#include "matloader_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <matloaderwidget.h>

class MATLOADERSHARED_EXPORT MatLoader:public IPlugin
{
public:
    MatLoader();

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

    void setParas(std::string fileName,int mode);
private:
    //定义内部参数
    MatLoaderWidget *pluginWidget;
    std::string fileName;
    int imReadMode;
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(MatLoader)
};
REGISTER_REFLEX(MatLoader)

#endif // TESTPLUGIN_H
