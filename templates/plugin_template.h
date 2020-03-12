#ifndef TARGET_NAME_AUTO_REPLACED_H
#define TARGET_NAME_AUTO_REPLACED_H

#include "FILE_NAME_AUTO_REPLACED_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <FILE_WIDGET_AUTO_REPLACED.h>

class TARGET_NAME_AUTO_REPLACEDSHARED_EXPORT PLUGIN_NAME_AUTO_REPLACED:public IPlugin
{
public:
    PLUGIN_NAME_AUTO_REPLACED();

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
    PLUGIN_WIDGET_AUTO_REPLACED *pluginWidget;
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(PLUGIN_NAME_AUTO_REPLACED)
};
REGISTER_REFLEX(PLUGIN_NAME_AUTO_REPLACED)

#endif // TESTPLUGIN_H
