#include "mattofile.h"
#include <string>
#include <QObject>
#include <QDir>
#include <opencv2/opencv.hpp>
#include <QRegExp>

MatToFile::MatToFile()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new MatToFileWidget();
    fileName="";
    path=QDir::currentPath();
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->initParas(fileName,path);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&MatToFileWidget::requestAction,[=](QString name,QString path){
       this->fileName=name;
       this->path=path;
       this->requestInputs();
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int MatToFile::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> MatToFile::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("class cv::Mat");
    
    return inputTypes;
}

int MatToFile::getOutputCount()
{
    //这里设置输出参数个数
    return 0;
}

std::vector<std::string> MatToFile::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	
    return outputTypes;
}


void MatToFile::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    if(this->fileName!=""&&this->path!=""){
        if(fileName.indexOf(".jpg")==-1&&fileName.indexOf(".jpeg")==-1&&fileName.indexOf(".png")==-1&&
                fileName.indexOf(".bmp")==-1&&fileName.indexOf(".tiff")==-1){
            fileName+=".png";
        }
        setProgress(10);
        cv::imwrite((this->path+"/"+this->fileName).toStdString(),Any(m_inputs[0]).getData<cv::Mat>());
        setProgress(100);
        setProgress(-1);
    }
}

void MatToFile::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();

}

QWidget *MatToFile::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string MatToFile::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool MatToFile::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string MatToFile::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "no documentation";
}

std::vector<std::string> MatToFile::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("the OpenCV image to write");
    
    return info;
}

std::vector<std::string> MatToFile::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	
    return info;
}
