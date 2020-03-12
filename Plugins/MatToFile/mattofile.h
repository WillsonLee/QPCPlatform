#ifndef MATTOFILE_H
#define MATTOFILE_H

#include "mattofile_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <mattofilewidget.h>

class MATTOFILESHARED_EXPORT MatToFile:public IPlugin
{
public:
    MatToFile();

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
    MatToFileWidget *pluginWidget;
    QString fileName;
    QString path;
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(MatToFile)
};
REGISTER_REFLEX(MatToFile)

#endif // TESTPLUGIN_H
