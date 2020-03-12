#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

#include "testplugin_global.h"
#include <Any.h>
#include <iplugin.h>
#include <testwidget.h>
#include <reflex.h>

class TESTPLUGINSHARED_EXPORT TestPlugin:public IPlugin
{
public:
    TestPlugin();

    // IPlugin interface
public:
    int getInputCount();
    std::vector<std::string> getInputTypes();
    int getOutputCount();
    std::vector<std::string> getOutputTypes();
    void run();
    void cleanGarbage(std::vector<Any> &outputVars, const std::vector<bool> targets);
    QWidget *getWidget();
    std::string getDoc();
    std::vector<std::string> getInputInfo();
    std::vector<std::string> getOutputInfo();
    void setInternalArgs(int a, int b, int c);
private:
    int m_a;
    int m_b;
    int m_c;
    TestWidget *testWidget;

    CONSTRUCTOR(TestPlugin)
};
REGISTER_REFLEX(TestPlugin)

#endif // TESTPLUGIN_H
