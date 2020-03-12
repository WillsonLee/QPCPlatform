#include "blobcluster.h"
#include <string>
#include <QObject>
#include <opencv2/opencv.hpp>
#include <QVector>
#include <QDebug>

BlobCluster::BlobCluster()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new BlobClusterWidget();
    fourNeighbors=false;
    outType=0;
    removal=false;
    area=100;
    types.push_back(CV_32S);
    types.push_back(CV_16U);
    algoIndex=0;
    algorithms.push_back(cv::CCL_GRANA);
    algorithms.push_back(cv::CCL_WU);
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->initArgs(fourNeighbors,outType,algoIndex,removal,area);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&BlobClusterWidget::internalArgsChanged,[=](bool four,int type,int algo,bool rem,int area_){
        fourNeighbors=four;
        outType=type;
        algoIndex=algo;
        removal=rem;
        area=area_;
        this->requestInputs();
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int BlobCluster::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> BlobCluster::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("class cv::Mat");
    
    return inputTypes;
}

int BlobCluster::getOutputCount()
{
    //这里设置输出参数个数
    return 2;
}

std::vector<std::string> BlobCluster::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
    outputTypes.push_back("class cv::Mat");
    outputTypes.push_back("class cv::Mat");
//    outputTypes.push_back(std::string(typeid(QVector<QVector<int> >).name()));
    return outputTypes;
}


void BlobCluster::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat src=Any(m_inputs[0]).getData<cv::Mat>();
    if(src.type()!=CV_8UC1){
        throw std::exception("plugin BlobCluster can only handle single channel binary image (image type()==CV_8UC1)");
    }
    cv::Mat *dst=new cv::Mat();
    cv::Mat stats;
    cv::Mat centroid;
    int pro=0;
    setProgress(pro);
    cv::connectedComponentsWithStats(src,*dst,stats,centroid,this->fourNeighbors?4:8,types.at(outType),algorithms.at(algoIndex));
    pro=removal?50:100;
    setProgress(pro);
    QVector<int> labs;
    cv::Mat *statsMat=new cv::Mat(0,1,CV_32SC(6));
    for(int r=0;r<dst->rows;++r){
        for(int c=0;c<dst->cols;++c){
            //对所有元素其对应label的面积小于一定阈值的将其label设为0
            int label=0;
            if(types.at(outType)==CV_32S){
                label=dst->at<int>(r,c);
            }
            else{
                label=(int)dst->at<ushort>(r,c);
            }
            if(label!=0){
                if(removal&&stats.at<int>(label,cv::CC_STAT_AREA)<area){
                    dst->at<int>(r,c)=0;
                }
                else if(!labs.contains(label)){
                    //在statsMat中依次记录每个连接成分的label,top,left,width,height和area值(每个占一列)
                    labs.push_back(label);
                    cv::Mat record(1,1,CV_32SC(6));
                    cv::Vec6i *ptr=record.ptr<cv::Vec6i>(0);
                    ptr[0][0]=label;
                    ptr[0][1]=stats.at<int>(label,cv::CC_STAT_TOP);
                    ptr[0][2]=stats.at<int>(label,cv::CC_STAT_LEFT);
                    ptr[0][3]=stats.at<int>(label,cv::CC_STAT_WIDTH);
                    ptr[0][4]=stats.at<int>(label,cv::CC_STAT_HEIGHT);
                    ptr[0][5]=stats.at<int>(label,cv::CC_STAT_AREA);
                    statsMat->push_back(record);
                }
            }
        }
        int prog=int(float(r)/dst->rows*50+50);
        if(prog>pro){
            pro=prog;
            setProgress(pro);
        }
    }
    setProgress(100);
    std::vector<Any> outs;
    outs.push_back(*dst);
    outs.push_back(*statsMat);
    std::vector<int> changed(2,1);
    setOutputs(outs,changed);
}

void BlobCluster::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    if(targets[0]){
        Any(outputVars[0]).clean<cv::Mat>();
    }
    if(targets[1]){
        Any(outputVars[1]).clean<cv::Mat>();
    }
}

QWidget *BlobCluster::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string BlobCluster::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool BlobCluster::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string BlobCluster::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "connected components analysis plugin";
}

std::vector<std::string> BlobCluster::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("opencv binary image");
    
    return info;
}

std::vector<std::string> BlobCluster::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
    info.push_back("blob labels image");
    info.push_back("stats of the connected components (each channel corresponds to label,top,left,width,height and area respectively)");
    return info;
}
