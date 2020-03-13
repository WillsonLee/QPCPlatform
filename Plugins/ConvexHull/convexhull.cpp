#include "convexhull.h"
#include <string>
#include <QObject>
#include <Utils.h>
#include <QtConcurrent/QtConcurrent>

ConvexHull::ConvexHull()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new ConvexHullWidget();
    binary=true;
    algo=0;//表示使用的外包多边形算法:0-javis,1-graham
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->initArgs(binary,algo);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&ConvexHullWidget::argsChanged,[=](bool bin,int algo){
        this->binary=bin;
        this->algo=algo;
        this->requestInputs();
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;
}

int ConvexHull::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> ConvexHull::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("class cv::Mat");
    
    return inputTypes;
}

int ConvexHull::getOutputCount()
{
    //这里设置输出参数个数
    return 2;
}

std::vector<std::string> ConvexHull::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	outputTypes.push_back("class cv::Mat");
    outputTypes.push_back("class cv::Mat");
    
    return outputTypes;
}


void ConvexHull::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat src=Any(m_inputs[0]).getData<cv::Mat>();
    if(src.channels()!=1){
        throw std::logic_error("the input image should be single channel binary or multi-label image!");
    }
    setProgress(0);
    if(binary){
        std::vector<cv::Point> points;
        cv::Mat src8U;
        src.convertTo(src8U,CV_8UC1);
        int pro=0;
        for(int i=0;i<src8U.rows;++i){
            uchar *p=src8U.ptr<uchar>(i);
            for(int j=0;j<src8U.cols;++j){
                if(p[j]!=0){
                    points.push_back(cv::Point(j,i));
                }
            }
            int prog=float(i)/src8U.rows*50;
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        std::vector<std::vector<cv::Point> > polys;
        polys.push_back(std::vector<cv::Point>());
        this->convexhull(points,polys[0],this->algo);
        setProgress(80);
        cv::Mat singles[3]={src8U,src8U.clone(),src8U.clone()};
        cv::Mat *polygon=new cv::Mat(src8U.rows,src8U.cols,CV_8UC3);
        cv::merge(singles,3,*polygon);
        cv::polylines(*polygon,polys[0],true,cv::Scalar(0,0,255,0),3);
        setProgress(90);
        cv::Mat *filledMask=new cv::Mat(src8U.rows,src8U.cols,CV_8UC1,cv::Scalar(0));
        cv::fillPoly(*filledMask,polys,cv::Scalar(255));
        setProgress(100);
        std::vector<Any> outs;
        outs.push_back(Any(*polygon));
        outs.push_back(Any(*filledMask));
        setOutputs(outs,std::vector<int>(2,1));
    }
    else{
        QMap<int,std::vector<cv::Point> > labelAndPts;
        cv::Mat src32S;
        src.convertTo(src32S,CV_32SC1);
        int pro=0;
        for(int i=0;i<src32S.rows;++i){
            int *p=src32S.ptr<int>(i);
            for(int j=0;j<src32S.cols;++j){
                if(p[j]!=0){
                    if(!labelAndPts.contains(p[j])){
                        labelAndPts.insert(p[j],std::vector<cv::Point>());
                    }
                    labelAndPts[p[j]].push_back(cv::Point(j,i));
                }
            }
            int prog=float(i)/src32S.rows*45;
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        QMap<int,std::vector<std::vector<cv::Point> > > vertices;
        int count=0;
        for(auto key:labelAndPts.keys()){
            std::vector<std::vector<cv::Point> >ptsi;
            ptsi.push_back(std::vector<cv::Point>());
            vertices[key]=ptsi;
            this->convexhull(labelAndPts[key],vertices[key][0],this->algo);
            count++;
            int prog=float(count)/labelAndPts.size()*45+45;
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        setProgress(90);
        cv::Mat src8U;
        src.convertTo(src8U,CV_8UC1);
        cv::Mat singles[3]={src8U,src8U.clone(),src8U.clone()};
        cv::Mat *polygon=new cv::Mat(src32S.rows,src32S.cols,CV_8UC3);
        cv::merge(singles,3,*polygon);
        cv::Mat *filledMask=new cv::Mat(src32S.rows,src32S.cols,src.type(),cv::Scalar(0));
        for(auto key:labelAndPts.keys()){
            cv::polylines(*polygon,vertices[key][0],true,cv::Scalar(0,0,255,0),3);
            cv::fillPoly(*filledMask,vertices[key],cv::Scalar(key));
        }
        setProgress(100);
        std::vector<Any> outs;
        outs.push_back(Any(*polygon));
        outs.push_back(Any(*filledMask));
        setOutputs(outs,std::vector<int>(2,1));
    }
}

void ConvexHull::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    for(auto i:{0,1}){
        if(targets[i])Any(outputVars[i]).clean<cv::Mat>();
    }
}

QWidget *ConvexHull::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string ConvexHull::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool ConvexHull::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string ConvexHull::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "find the convex hull of the image";
}

std::vector<std::string> ConvexHull::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("input image (either binatry or multi label single channel image)");
    
    return info;
}

std::vector<std::string> ConvexHull::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	info.push_back("border image");
    info.push_back("internal area mask image");
    
    return info;
}

void ConvexHull::convexhull(const std::vector<cv::Point> &pts, std::vector<cv::Point> &vertices, int algo)
{
    switch (algo) {
    case 0:
        lyxutils::algorithms::javisMarch(pts,vertices);
        break;
    case 1:
        lyxutils::algorithms::findConvexHullBorder(pts,vertices);
        break;
    default:
        break;
    }
}
