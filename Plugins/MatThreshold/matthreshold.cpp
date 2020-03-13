#include "matthreshold.h"
#include <string>
#include <QObject>
#include <opencv2/opencv.hpp>
#include <QMap>

MatThreshold::MatThreshold()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new MatThresholdWidget();
    thresh=0;
    max_value=255;
    typeCollection["BINARY"]=cv::THRESH_BINARY;
    typeCollection["BINARY_INV"]=cv::THRESH_BINARY_INV;
    typeCollection["TRUNC"]=cv::THRESH_TRUNC;
    typeCollection["TOZERO"]=cv::THRESH_TOZERO;
    typeCollection["TOZERO_INV"]=cv::THRESH_TOZERO_INV;
    typeCollection["MASK"]=cv::THRESH_MASK;
    typeCollection["OTSU"]=cv::THRESH_OTSU;
    typeCollection["TRIANGLE"]=cv::THRESH_TRIANGLE;
    type="BINARY";
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->resetSelection(typeCollection.keys());
    pluginWidget->initArgs(thresh,max_value,type);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&MatThresholdWidget::internalArgsChanged,[=](double thresh,double max,QString type){
        bool changed=false;
        if(this->thresh!=thresh){
            this->thresh=thresh;
            changed=true;
        }
        if(this->max_value!=max){
            this->max_value=max;
            changed=true;
        }
        if(this->type!=type){
            this->type=type;
            changed=true;
        }
        if(changed){
            requestInputs();
        }
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int MatThreshold::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> MatThreshold::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("class cv::Mat");
    
    return inputTypes;
}

int MatThreshold::getOutputCount()
{
    //这里设置输出参数个数
    return 1;
}

std::vector<std::string> MatThreshold::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	outputTypes.push_back("class cv::Mat");
    
    return outputTypes;
}


void MatThreshold::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat src=Any(m_inputs[0]).getData<cv::Mat>();
    setProgress(0);
    if(src.channels()>1&&(type=="OTSU"||type=="TRIANGLE")){
        this->typeCollection.remove("OTSU");
        this->typeCollection.remove("TRIANGLE");
        QList<QString> items=typeCollection.keys();
        pluginWidget->resetSelection(items);
        throw std::logic_error("the thresh type THRESH_OTSU and THRESH_TRIANGLE can only be applied to single channel image!");
    }
    else{
        if(!typeCollection.contains("OTSU")){
            typeCollection["OTSU"]=cv::THRESH_OTSU;
            typeCollection["TRIANGLE"]=cv::THRESH_TRIANGLE;
            QList<QString> items=typeCollection.keys();
            pluginWidget->resetSelection(items);
        }
    }
    setProgress(20);
    cv::Mat *dst=new cv::Mat();
    cv::Mat src2=src.clone();
    if(src2.type()==CV_32SC(src2.channels())){
        src2.convertTo(src2,CV_32FC(src2.channels()));//不支持32SC型故转成32FC型
    }
    setProgress(60);
    cv::threshold(src2,*dst,thresh,max_value,typeCollection[type]);
    setProgress(100);
    if(dst->rows>0&&dst->cols>0){
        setOutputs(std::vector<Any>(1,Any(*dst)),std::vector<int>(1,1));
    }
}

void MatThreshold::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    if(targets[0])Any(outputVars[0]).clean<cv::Mat>();
}

QWidget *MatThreshold::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string MatThreshold::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool MatThreshold::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string MatThreshold::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "apply thresholding to opencv image";
}

std::vector<std::string> MatThreshold::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("input image");
    
    return info;
}

std::vector<std::string> MatThreshold::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	info.push_back("output image");
    
    return info;
}
