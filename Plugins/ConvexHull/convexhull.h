#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include "convexhull_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <convexhullwidget.h>
#include <opencv2/opencv.hpp>

class CONVEXHULLSHARED_EXPORT ConvexHull:public IPlugin
{
public:
    ConvexHull();

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
    ConvexHullWidget *pluginWidget;
    bool binary;
    int algo;
    void convexhull(const std::vector<cv::Point> &pts,std::vector<cv::Point> &vertices,int algo);
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(ConvexHull)
};
REGISTER_REFLEX(ConvexHull)

#endif // TESTPLUGIN_H
