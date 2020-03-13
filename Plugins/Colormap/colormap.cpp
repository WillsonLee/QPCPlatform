#include "colormap.h"
#include <string>
#include <QObject>
#include <random>
#include <QTime>

Colormap::Colormap()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new ColormapWidget();
    bins=100;
    maxBins=true;
    min_color=cv::Scalar(255,255,255);
    max_color=cv::Scalar(0,0,0);
    randomColor=true;
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->initArgs(randomColor,bins,maxBins);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&ColormapWidget::internalArgsChanged,[=](bool randomColor,int bins,bool maxBins,cv::Scalar min_color,cv::Scalar max_color){
        this->randomColor=randomColor;
        this->bins=bins;
        this->maxBins=maxBins;
        this->min_color=min_color;
        this->max_color=max_color;
        this->requestInputs();
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int Colormap::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> Colormap::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("class cv::Mat");
    
    return inputTypes;
}

int Colormap::getOutputCount()
{
    //这里设置输出参数个数
    return 1;
}

std::vector<std::string> Colormap::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	outputTypes.push_back("class cv::Mat");
    
    return outputTypes;
}


void Colormap::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat src=Any(m_inputs[0]).getData<cv::Mat>();
    if(src.channels()!=1){
        throw std::logic_error("Colormap plugin only support single channel immage!");
    }
    int pro=0;
    float factor=randomColor?100:50;
    float shift=randomColor?0:50;
    setProgress(pro);
    this->min_gray=accessMat(src,0,0);
    this->max_gray=accessMat(src,0,0);
    if(!randomColor){
        for(int i=0;i<src.rows;++i){
            for(int j=0;j<src.cols;++j){
                double g=accessMat(src,i,j);
                this->min_gray=g<this->min_gray?g:this->min_gray;
                this->max_gray=g>this->max_gray?g:this->max_gray;
                int prog=int(float(i)/src.rows*factor);
                if(prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
            }
        }
    }
    this->colors.clear();
    cv::Mat *outMat=new cv::Mat(src.rows,src.cols,CV_8UC3);
    for(int i=0;i<src.rows;++i){
        for(int j=0;j<src.cols;++j){
            cv::Scalar c=colormap(accessMat(src,i,j));
            outMat->at<cv::Vec3b>(i,j)=cv::Vec3b(c[0],c[1],c[2]);
            int prog=int(float(i)/src.rows*factor+shift);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
    }
    setProgress(100);
    setOutputs(std::vector<Any>(1,Any(*outMat)),std::vector<int>(1,1));
}

void Colormap::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    if(targets[0])Any(outputVars[0]).clean<cv::Mat>();
}

QWidget *Colormap::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string Colormap::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool Colormap::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string Colormap::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "convert the input single channel image to pseudo color image";
}

std::vector<std::string> Colormap::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("single channel opencv image");
    
    return info;
}

std::vector<std::string> Colormap::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	info.push_back("8 bit 3 channel image");
    
    return info;
}

double Colormap::accessMat(cv::Mat &src, int row, int col)
{
    if(row>=0&&row<src.rows&&col>=0&&col<src.cols){
        int n=src.channels();
        if(src.type()==CV_8UC(n)){
            return double(*src.ptr<uchar>(row,col));
        }
        else if(src.type()==CV_8SC(n)){
            return double(*src.ptr<schar>(row,col));
        }
        else if(src.type()==CV_16UC(n)){
            return double(*src.ptr<ushort>(row,col));
        }
        else if(src.type()==CV_16SC(n)){
            return double(*src.ptr<short>(row,col));
        }
        else if(src.type()==CV_32SC(n)){
            return double(*src.ptr<int>(row,col));
        }
        else if(src.type()==CV_32FC(n)){
            return double(*src.ptr<float>(row,col));
        }
        else if(src.type()==CV_64FC(n)){
            return *src.ptr<double>(row,col);
        }
        else{
            throw std::runtime_error("In Colormap:mat access unsupported image type!");
        }
    }
    else{
        throw std::runtime_error("In Colormap:mat access out of range exception!");
    }
}

cv::Scalar Colormap::colormap(double gray)
{
    if(randomColor){
        if(colors.contains(gray))return colors[gray];
        auto randColor=[=]()->cv::Scalar{qsrand(QTime::currentTime().msec());return cv::Scalar(qrand()%256,qrand()%256,qrand()%256);};
        cv::Scalar c=randColor();
        while(c[0]<128&&c[1]<128&&c[2]<128){//暗色调不要
            c=randColor();
        }
        colors[gray]=c;
        return c;
    }
    else{
        if(min_gray==max_gray)return (min_color+max_color)/2;
        if(maxBins){
            return min_color*(max_gray-gray)/(max_gray-min_gray)+max_color*(gray-min_gray)/(max_gray-min_gray);
        }
        else{
            double interval=(max_gray-min_gray)/bins;
            int gray_level=int((gray-min_gray)/interval);
            return min_color*(bins-1-gray_level)/(bins-1)+max_color*gray_level/(bins-1);
        }
    }
}
