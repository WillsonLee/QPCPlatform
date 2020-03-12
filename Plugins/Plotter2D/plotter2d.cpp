#include "plotter2d.h"
#include <string>
#include <QObject>
#include <opencv2/opencv.hpp>

Plotter2D::Plotter2D()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new Plotter2DWidget();
//    delegate=new PlotterSinalDelegate();
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化

    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(&this->messenger,&SignalDelegate::inputDataChanged,this->pluginWidget,&Plotter2DWidget::onDataChange);
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;
    this->inputsValidityRequired=false;//让外界插件不需要检查输入都准备就绪
}

int Plotter2D::getInputCount()
{
    //这里设置插件的输入参数个数
    return 2;
}

std::vector<std::string> Plotter2D::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("null");
    inputTypes.push_back("null");
    
    return inputTypes;
}

int Plotter2D::getOutputCount()
{
    //这里设置输出参数个数
    return 0;
}

std::vector<std::string> Plotter2D::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	
    return outputTypes;
}


void Plotter2D::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    setProgress(0);
    QVector<double> x,y;
    this->getInputs(x,y);
    setProgress(50);
    this->messenger.sendSignal(x,y);
    setProgress(100);
    setProgress(-1);
}

void Plotter2D::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();

}

QWidget *Plotter2D::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string Plotter2D::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool Plotter2D::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string Plotter2D::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "plot the input 2D data either as scatter plot or as continuous plot";
}

std::vector<std::string> Plotter2D::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("x input data (the type should be single row or column cv::Mat or a QVector or a std::vector)");
    info.push_back("y input data (the type should be single row or column cv::Mat or a QVector or a std::vector)");
    
    return info;
}

std::vector<std::string> Plotter2D::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	
    return info;
}

void Plotter2D::getInputs(QVector<double> &x, QVector<double> &y)
{
    //外界不检查自己需检查
    Any xData=Any(m_inputs[0]);
    Any yData=Any(m_inputs[1]);
    if(xData.isNull()&&yData.isNull()){//两者都为NULL则没数据,不符合要求
        throw std::exception("Both inputs x and y data are null!The plugin require at least one input to be valid!");
    }
    std::string tx=std::string(xData.getType());
    std::string ty=std::string(yData.getType());
    //数据x
    if(tx==std::string(typeid(cv::Mat).name())){
        cv::Mat src=xData.getData<cv::Mat>();
        if(src.rows==1||src.cols==1){
            cv::Mat dst;
            src.convertTo(dst,CV_64FC1);
            x=QVector<double>::fromStdVector((std::vector<double>)(dst));
        }
        else{
            throw std::exception("input data of cv::Mat type should be single row or single column!");
        }
    }
    else if(tx==std::string(typeid(QVector<double>).name())){
        x=xData.getData<QVector<double> >();
    }
    else if(tx==std::string(typeid(std::vector<double>).name())){
        x=QVector<double>::fromStdVector(xData.getData<std::vector<double> >());
    }
    else if(tx=="null"){}//留待之后处理
    else{
        throw std::exception("data type of x is not allowed!Input x should be single row/col cv::Mat or a QVector<double> or a std::vector<double>!");
    }
    //数据y
    if(ty==std::string(typeid(cv::Mat).name())){
        cv::Mat src=yData.getData<cv::Mat>();
        if(src.rows==1||src.cols==1){
            cv::Mat dst;
            src.convertTo(dst,CV_64FC1);
            y=QVector<double>::fromStdVector((std::vector<double>)(dst));
        }
        else{
            throw std::exception("input data of cv::Mat type should be single row or single column!");
        }
    }
    else if(ty==std::string(typeid(QVector<double>).name())){
        y=yData.getData<QVector<double> >();
    }
    else if(ty==std::string(typeid(std::vector<double>).name())){
        y=QVector<double>::fromStdVector(yData.getData<std::vector<double> >());
    }
    else if(ty=="null"){}//留待之后处理
    else{
        throw std::exception("data type of y is not allowed!Input y should be single row/col cv::Mat or a QVector<double> or a std::vector<double>!");
    }
    if(xData.isNull()){//如果x,y其中一个为NULL另一个不是,则为NULL的那个取用默认的递增数据
        x=QVector<double>(y.size());
        for(int i=0;i<x.size();++i){
            x[i]=i+1;
        }
    }
    if(yData.isNull()){
        y=QVector<double>(x.size());
        for(int i=0;i<y.size();++i){
            y[i]=i+1;
        }
    }
    if(x.size()!=y.size()){//如果两个向量维数不等,以小的为准,大的向量多余数据忽略
        int sz=x.size()<y.size()?x.size():y.size();
        while(x.size()>sz){
            x.pop_back();
        }
        while(y.size()>sz){
            y.pop_back();
        }
    }
}
