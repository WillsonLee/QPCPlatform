#include "grayconverter.h"
#include <string>
#include <QObject>
#include <opencv2/opencv.hpp>
#include <QTime>

GrayConverter::GrayConverter()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    

    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化

    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上

    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int GrayConverter::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> GrayConverter::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("class cv::Mat");

    return inputTypes;
}

int GrayConverter::getOutputCount()
{
    //这里设置输出参数个数
    return 1;
}

std::vector<std::string> GrayConverter::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	outputTypes.push_back("class cv::Mat");

    return outputTypes;
}


void GrayConverter::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat *matOut=new cv::Mat();
    Any anyIn=this->m_inputs[0];
    if(anyIn.getData<cv::Mat>().type()==CV_8UC3){
        cv::cvtColor(anyIn.getData<cv::Mat>(),*matOut,cv::COLOR_BGR2GRAY);
        std::vector<Any> outputs;
        outputs.push_back(Any().setData(*matOut));
        setOutputs(outputs,std::vector<int>(1,1));
    }
    else if(anyIn.getData<cv::Mat>().type()==CV_8UC1){
        *matOut=anyIn.getData<cv::Mat>();
        std::vector<Any> outputs;
        outputs.push_back(Any().setData(*matOut));
        setOutputs(outputs,std::vector<int>(1,1));
    }
    else if(anyIn.getData<cv::Mat>().type()==CV_8UC4){
        cv::cvtColor(anyIn.getData<cv::Mat>(),*matOut,cv::COLOR_BGRA2GRAY);
        std::vector<Any> outputs;
        outputs.push_back(Any().setData(*matOut));
        setOutputs(outputs,std::vector<int>(1,1));
    }
}

void GrayConverter::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    if(targets[0])Any(outputVars[0]).clean<cv::Mat>();
}

QWidget *GrayConverter::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return NULL;
}

std::string GrayConverter::saveState()
{
    //该函数用于保存该插件内部参数,并返回保存的文件名,这个函数不必要,如果实现必须与restoreState一起
    return "";
}

bool GrayConverter::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态
    return false;
}

std::string GrayConverter::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "no documentation";
}

std::vector<std::string> GrayConverter::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	
    return info;
}

std::vector<std::string> GrayConverter::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	
    return info;
}
