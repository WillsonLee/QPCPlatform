#include "testplugin.h"
#include <string>
#include <QObject>

TestPlugin::TestPlugin()
{
    this->m_a=20;
    this->m_b=20;
    this->m_c=20;
    testWidget=new TestWidget();
    testWidget->setInitialParas(this->m_a,this->m_b,this->m_c);
    QObject::connect(testWidget,&TestWidget::internalArgsChanged,[=](int a,int b,int c){
       this->setInternalArgs(a,b,c);
    });
//    embededWidget=true;
}

int TestPlugin::getInputCount()
{
    return 4;
}

std::vector<std::string> TestPlugin::getInputTypes()
{
    std::vector<std::string> inputTypes;
    inputTypes.push_back("int");
    inputTypes.push_back("float");
    inputTypes.push_back("double");
    inputTypes.push_back(TYPENAMEOFSTRING);
    return inputTypes;
}

void TestPlugin::run()
{
    this->setProgress(0);
    int a;
    float b;
    double c;
    std::string d;
    this->m_inputs[0].getData(a);
    this->m_inputs[1].getData(b);
    this->m_inputs[2].getData(c);
    this->m_inputs[3].getData(d);

    this->setProgress(50);
    //输出参数不可在栈上,必须在堆上,否则函数结束就消失了
    double *e=new double(this->m_a*a+this->m_b*b+this->m_c*c);
    std::string *f=new std::string(std::to_string(m_a)+"*"+std::to_string(a)+"+"+
                                   std::to_string(m_b)+"*"+std::to_string(b)+"+"+
                                   std::to_string(m_c)+"*"+std::to_string(c)+"="+std::to_string(*e)+"\t"+d);

    this->setProgress(80);
    std::vector<Any> outs;
    outs.push_back(*e);
    outs.push_back(*f);
    this->setOutputs(outs,std::vector<bool>(this->getOutputCount(),true));

    this->setProgress(100);

    this->setProgress(-1);
}

void TestPlugin::cleanGarbage(std::vector<Any> &outputVars, const std::vector<bool> targets)
{
    if(targets[0])outputVars[0].clean<double>();
    if(targets[1])outputVars[1].clean<std::string>();
}

QWidget *TestPlugin::getWidget()
{
    return testWidget;
}

//bool TestPlugin::openParameterWin()
//{

//    if(this->testWidget->exec()==QDialog::Accepted){
//        this->testWidget->collectData(this->m_a,this->m_b,this->m_c);
//        return true;
//    }
//    else{
//        return false;
//    }
//}

std::string TestPlugin::getDoc()
{
    return "this is the documentation and this has not been modified!";
}

std::vector<std::string> TestPlugin::getInputInfo()
{
    std::vector<std::string> info;
    info.push_back("一个整型int");
    info.push_back("一个浮点型float");
    info.push_back("一个双精度浮点型double");
    info.push_back("一个字符串类型");
    return info;
}

std::vector<std::string> TestPlugin::getOutputInfo()
{
    std::vector<std::string> info;
    info.push_back("各个输入数字的乘积和:ax1+bx2+cx3");
    info.push_back("各个输入参数的字符串连接");
    return info;
}

void TestPlugin::setInternalArgs(int a, int b, int c)
{
    this->m_a=a;
    this->m_b=b;
    this->m_c=c;
}

int TestPlugin::getOutputCount()
{
    return 2;
}

std::vector<std::string> TestPlugin::getOutputTypes()
{
    std::vector<std::string> outputsT;
    outputsT.push_back("double");
    outputsT.push_back(TYPENAMEOFSTRING);
    return outputsT;
}
