#ifndef COLORMAP_H
#define COLORMAP_H

#include "colormap_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <colormapwidget.h>
#include <opencv2/opencv.hpp>
#include <QMap>

class COLORMAPSHARED_EXPORT Colormap:public IPlugin
{
public:
    Colormap();

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
    ColormapWidget *pluginWidget;
    int bins;
    bool maxBins;
    double min_gray;
    double max_gray;
    cv::Scalar min_color;
    cv::Scalar max_color;
    bool randomColor;
    QMap<double,cv::Scalar> colors;
    double accessMat(cv::Mat &src, int row, int col);
    cv::Scalar colormap(double gray);
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(Colormap)
};
REGISTER_REFLEX(Colormap)

#endif // TESTPLUGIN_H
