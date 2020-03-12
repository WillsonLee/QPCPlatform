#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H

#include "morphology_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <morphologywidget.h>
#include <opencv2/opencv.hpp>
#include <QVector>

class MORPHOLOGYSHARED_EXPORT Morphology:public IPlugin
{
public:
    Morphology();

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
    MorphologyWidget *pluginWidget;
    int morphType;
    int shape;
    int width;
    int height;
    int anchorX;
    int anchorY;
    int iter;
    int borderType;
    cv::Scalar borderValue;
    QVector<int> allMorphTypes;
    QVector<int> allShapes;
    QVector<int> allBorderTypes;
private:
    void checkAndChange(int src,int &dst,bool &changed);
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(Morphology)
};
REGISTER_REFLEX(Morphology)

#endif // TESTPLUGIN_H
