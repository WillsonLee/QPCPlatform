#include "houghlines.h"
#include <string>
#include <QObject>
#include <opencv2/opencv.hpp>
#include <Utils.h>

HoughLines::HoughLines()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new HoughLinesWidget();
    rho=1;
    theta=1;
    threshold=100;
    minLineLength=6;
    maxGap=1;
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->initArgs(rho,theta,threshold,minLineLength,maxGap);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&HoughLinesWidget::argsChanged,[=](double rho,double theta,int thresh,double minLength,double maxGap){
        if(this->rho!=rho||this->theta!=theta||this->threshold!=thresh||this->minLineLength!=minLength||this->maxGap!=maxGap){//any changes
            this->rho=rho;
            this->theta=theta;
            this->threshold=thresh;
            this->minLineLength=minLength;
            this->maxGap=maxGap;
            this->requestInputs();
        }
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int HoughLines::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> HoughLines::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("cv::Mat");
    
    return inputTypes;
}

int HoughLines::getOutputCount()
{
    //这里设置输出参数个数
    return 2;
}

std::vector<std::string> HoughLines::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
    outputTypes.push_back("cv::Mat");
    outputTypes.push_back("std::vector<cv::Vec4i>");
    
    return outputTypes;
}


void HoughLines::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat src=Any(m_inputs[0]).getData<cv::Mat>();
    if(src.type()!=CV_8UC1){
        throw std::runtime_error("the hough line detection plugin only surpport 8bit single channel binary image!(type==CV_8UC1");
    }
    setProgress(10);
    src=src.clone();//houghLinesP may modify the image, so should be cloned in case changes happens
    cv::Mat *outMat=new cv::Mat();
    std::vector<cv::Mat> channels;
    for(auto i:{1,2,3})channels.push_back(src.clone());
    setProgress(30);
    cv::merge(channels,*outMat);
    setProgress(40);
    std::vector<cv::Vec4i> *vec=new std::vector<cv::Vec4i>();
    cv::HoughLinesP(src,*vec,this->rho,this->theta*CV_PI/180,this->threshold,this->minLineLength,this->maxGap);
    setProgress(70);
    np::apply(*vec,[&](cv::Vec4i vec){cv::line(*outMat,cv::Point(vec[0],vec[1]),cv::Point(vec[2],vec[3]),cv::Scalar(0,0,255),1);});
    setProgress(100);
    std::vector<Any> outs;
    outs.push_back(Any(*outMat));
    outs.push_back(Any(*vec));
    setOutputs(outs,std::vector<int>(2,1));
}

void HoughLines::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    if(targets[0]){
        Any(outputVars[0]).clean<cv::Mat>();
    }
    if(targets[1]){
        Any(outputVars[1]).clean<std::vector<cv::Vec4i> >();
    }
}

QWidget *HoughLines::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string HoughLines::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool HoughLines::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string HoughLines::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "this plugin detect straight lines using hough transform";
}

std::vector<std::string> HoughLines::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("binary image");
    
    return info;
}

std::vector<std::string> HoughLines::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	info.push_back("output image that displays the detected lines");
    info.push_back("detected straight lines");
    
    return info;
}
