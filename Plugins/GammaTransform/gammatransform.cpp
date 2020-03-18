#include "gammatransform.h"
#include <string>
#include <QObject>

GammaTransform::GammaTransform()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new GammaTransformWidget();
    double gamma=1;
    this->table=getLookUpTable(gamma);
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->initArgs(gamma);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&GammaTransformWidget::internalArgsChanged,[=](double gamma){
        this->table=getLookUpTable(gamma);
        requestInputs();
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int GammaTransform::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> GammaTransform::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("cv::Mat");
    
    return inputTypes;
}

int GammaTransform::getOutputCount()
{
    //这里设置输出参数个数
    return 1;
}

std::vector<std::string> GammaTransform::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	outputTypes.push_back("cv::Mat");
    
    return outputTypes;
}


void GammaTransform::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat src=Any(m_inputs[0]).getData<cv::Mat>();
    int channel=src.channels();
    if(src.type()!=CV_8UC(channel)){
        throw std::logic_error("Plugin GammaTransform can only be applied to 8 bits image (Mat object of type CV_8UC(n)");
    }
    setProgress(30);
    cv::Mat *dst=new cv::Mat();
    cv::LUT(src,this->table,*dst);
    std::vector<Any> outputs(1,Any().setData(*dst));
    std::vector<int> changed(1,1);
    setOutputs(outputs,changed);
}

void GammaTransform::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    if(targets[0])Any(outputVars[0]).clean<cv::Mat>();
}

QWidget *GammaTransform::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string GammaTransform::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool GammaTransform::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string GammaTransform::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "gamma transform the input opencv image";
}

std::vector<std::string> GammaTransform::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("input image");
    
    return info;
}

std::vector<std::string> GammaTransform::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	info.push_back("output image");
    
    return info;
}

cv::Mat GammaTransform::getLookUpTable(double gamma)
{
    cv::Mat lookUpTable(1,256,CV_8U);
    uchar *p=lookUpTable.ptr();
    for(int i=0;i<256;++i){
        p[i]=cv::saturate_cast<uchar>(std::pow(i/255.0,gamma)*255);
    }
    return lookUpTable;
}
