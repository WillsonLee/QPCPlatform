#include "mataccess.h"
#include <string>
#include <QObject>
#include <opencv2/opencv.hpp>

MatAccess::MatAccess()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new MatAccessWidget();
    row=0;
    col=0;
    channel=0;
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->setMaximum(10,10,2);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&MatAccessWidget::internalArgsChanged,[=](int row,int col,int cha){
        this->row=row;
        this->col=col;
        this->channel=cha;
        this->requestInputs();
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int MatAccess::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> MatAccess::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("cv::Mat");
    
    return inputTypes;
}

int MatAccess::getOutputCount()
{
    //这里设置输出参数个数
    return 1;
}

std::vector<std::string> MatAccess::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	outputTypes.push_back("double");
    
    return outputTypes;
}


void MatAccess::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat src=Any(m_inputs[0]).getData<cv::Mat>();
    pluginWidget->setMaximum(src.rows-1,src.cols-1,src.channels()-1);
    double *outVar=new double(-1);
    if(src.type()==CV_8UC(src.channels())){
        *outVar=(double)(*(src.ptr<uchar>(row,col)+channel));
        pluginWidget->setDepthLabel("CV_8U");
    }
    else if(src.type()==CV_8SC(src.channels())){
        *outVar=(double)(*(src.ptr<schar>(row,col)+channel));
        pluginWidget->setDepthLabel("CV_8S");
    }
    else if(src.type()==CV_16UC(src.channels())){
        *outVar=(double)(*(src.ptr<ushort>(row,col)+channel));
        pluginWidget->setDepthLabel("CV_16U");
    }
    else if(src.type()==CV_16SC(src.channels())){
        *outVar=(double)(*(src.ptr<short>(row,col)+channel));
        pluginWidget->setDepthLabel("CV_16S");
    }
    else if(src.type()==CV_32SC(src.channels())){
        *outVar=(double)(*(src.ptr<int>(row,col)+channel));
        pluginWidget->setDepthLabel("CV_32S");
    }
    else if(src.type()==CV_32FC(src.channels())){
        *outVar=(double)(*(src.ptr<float>(row,col)+channel));
        pluginWidget->setDepthLabel("CV_32F");
    }
    else if(src.type()==CV_64FC(src.channels())){
        *outVar=*(src.ptr<double>(row,col)+channel);
        pluginWidget->setDepthLabel("CV_64F");
    }
    else{
        pluginWidget->setDepthLabel("unknown");
    }
    std::vector<Any> outs;
    outs.push_back(*outVar);
    setOutputs(outs,std::vector<int>(1,1));
}

void MatAccess::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    if(targets[0])Any(outputVars[0]).clean<double>();
}

QWidget *MatAccess::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string MatAccess::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool MatAccess::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string MatAccess::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "random access pixel value in Mat";
}

std::vector<std::string> MatAccess::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("opencv Mat image");
    
    return info;
}

std::vector<std::string> MatAccess::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	info.push_back("the accessed value");
    
    return info;
}
