#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "randomgenerator_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>


class RANDOMGENERATORSHARED_EXPORT RandomGenerator:public IPlugin
{
public:
    RandomGenerator();

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
    
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(RandomGenerator)
};
REGISTER_REFLEX(RandomGenerator)

#endif // TESTPLUGIN_H
