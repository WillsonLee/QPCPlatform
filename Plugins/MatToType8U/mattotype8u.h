#ifndef MATTOTYPE8U_H
#define MATTOTYPE8U_H

#include "mattotype8u_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <opencv2/opencv.hpp>


class MATTOTYPE8USHARED_EXPORT MatToType8U:public IPlugin
{
public:
    MatToType8U();

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
    double getValue(const cv::Mat &src,int row,int col,int channel);
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(MatToType8U)
};
REGISTER_REFLEX(MatToType8U)

#endif // TESTPLUGIN_H
