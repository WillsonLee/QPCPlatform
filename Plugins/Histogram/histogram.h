#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "histogram_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <histogramwidget.h>
#include <opencv2/opencv.hpp>

class HISTOGRAMSHARED_EXPORT Histogram:public IPlugin
{
public:
    Histogram();

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
    HistogramWidget *pluginWidget;
    int channels;
    bool norm;
    bool accumulate;
    int bins1;
    float min1;
    float max1;
    int bins2;
    float min2;
    float max2;
    int channel1;
    int channel2;
    int binsShift;//表示每个bins的取值相对于左边的偏移量,0表示bins取左值,1表示bins取中间值,2表示取右值
    bool isAuto1,isAuto2;
    template<class T>
    void assign(T &origin,T &rightVal,bool &changed){
        if(origin!=rightVal){
            origin=rightVal;
            changed=true;
        }
    }
    template<class T>
    void minMax(cv::Mat src,int channel,float &min,float &max){
        T* p=src.ptr<T>(0);
        min=float(p[channel]);
        max=float(p[channel]);
        int n=src.channels();
        for(int i=0;i<src.rows;++i){
            p=src.ptr<T>(i);
            for(int j=0;j<src.cols;++j){
                float value=float(p[j*n+channel]);
                min=value<min?value:min;
                max=value>max?value:max;
            }
        }
    }

	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(Histogram)
};
REGISTER_REFLEX(Histogram)

#endif // TESTPLUGIN_H
