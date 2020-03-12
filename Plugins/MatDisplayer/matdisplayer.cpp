#include "matdisplayer.h"
#include <string>
#include <QObject>
#include <opencv2/opencv.hpp>
#include <QTime>

MatDisplayer::MatDisplayer()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new MatDisplayerWidget();

    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化

    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上

    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int MatDisplayer::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> MatDisplayer::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
    inputTypes.push_back("class cv::Mat");

    return inputTypes;
}

int MatDisplayer::getOutputCount()
{
    //这里设置输出参数个数
    return 0;
}

std::vector<std::string> MatDisplayer::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	
    return outputTypes;
}


void MatDisplayer::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    Any any=this->m_inputs[0];
    cv::Mat src=any.getData<cv::Mat>();
    pluginWidget->setImage(src);
    setProgress(-1);
}

void MatDisplayer::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();

}

QWidget *MatDisplayer::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string MatDisplayer::saveState()
{
    //该函数用于保存该插件内部参数,并返回保存的文件名,这个函数不必要,如果实现必须与restoreState一起
    return "";
}

bool MatDisplayer::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态
    return false;
}

std::string MatDisplayer::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "no documentation";
}

std::vector<std::string> MatDisplayer::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	
    return info;
}

std::vector<std::string> MatDisplayer::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	
    return info;
}
