#include "histogram.h"
#include <string>
#include <QObject>
#include <QDebug>

Histogram::Histogram()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new HistogramWidget();
    channels=1;
    norm=false;
    accumulate=false;
    bins1=256;
    min1=0;
    max1=256;
    bins2=256;
    min2=0;
    max2=256;
    channel1=0;
    channel2=1;
    binsShift=1;//bins取中间值
    isAuto1=false;
    isAuto2=false;
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->initArgs(channels,norm,accumulate,bins1,min1,max1,bins2,min2,max2);
    pluginWidget->setBinsEdge(binsShift);
    pluginWidget->setAutoMinMax(isAuto1,isAuto2);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&HistogramWidget::internalArgsChanged,[=](int channels,bool norm,bool accumulate,
                     int bins1,float min1,float max1,int bins2,float min2,float max2){
        bool changed=false;
        this->assign(this->channels,channels,changed);
        this->assign(this->norm,norm,changed);
        this->assign(this->accumulate,accumulate,changed);
        this->assign(this->bins1,bins1,changed);
        this->assign(this->min1,min1,changed);
        this->assign(this->max1,max1,changed);
        this->assign(this->bins2,bins2,changed);
        this->assign(this->min2,min2,changed);
        this->assign(this->max2,max2,changed);
        if(changed){
            this->requestInputs();
        }
    });
    QObject::connect(pluginWidget,&HistogramWidget::channelsChanged,[=](int channel1,int channel2){
        bool changed=false;
        this->assign(this->channel1,channel1,changed);
        this->assign(this->channel2,channel2,changed);
        if(changed){
            this->requestInputs();
        }
    });
    QObject::connect(pluginWidget,&HistogramWidget::binsEdgeChanged,[=](int edge){
        if(this->binsShift!=edge){
            this->binsShift=edge;
            this->requestInputs();
        }
    });
    QObject::connect(pluginWidget,&HistogramWidget::binsRangeAutoChanged,[=](bool isAuto1,bool isAuto2){
        if(this->isAuto1!=isAuto1||this->isAuto2!=isAuto2){
            this->isAuto1=isAuto1;
            this->isAuto2=isAuto2;
            this->requestInputs();
        }
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int Histogram::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> Histogram::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("class cv::Mat");
    
    return inputTypes;
}

int Histogram::getOutputCount()
{
    //这里设置输出参数个数
    return 2;
}

std::vector<std::string> Histogram::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	outputTypes.push_back("class cv::Mat");
    outputTypes.push_back("class cv::Mat");
    return outputTypes;
}


void Histogram::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat src=Any(m_inputs[0]).getData<cv::Mat>();
    if(src.depth()!=CV_8U&&src.depth()!=CV_16U&&src.depth()!=CV_32F){
        src.convertTo(src,CV_32FC(src.channels()));
    }
    pluginWidget->setTotalChannels(src.channels());
    setProgress(5);
    int chans[]={channel1,channel2};
    int histSize[]={bins1,bins2};
    if(isAuto1){
        if(src.type()==CV_8UC(src.channels())){
            minMax<uchar>(src,channel1,min1,max1);
        }
        else if(src.type()==CV_16UC(src.channels())){
            minMax<ushort>(src,channel1,min1,max1);
        }
        else{
            minMax<float>(src,channel1,min1,max1);
        }
    }
    if(isAuto2){
        if(src.type()==CV_8UC(src.channels())){
            minMax<uchar>(src,channel2,min2,max2);
        }
        else if(src.type()==CV_16UC(src.channels())){
            minMax<ushort>(src,channel2,min2,max2);
        }
        else{
            minMax<float>(src,channel2,min1,max2);
        }
    }
    float r1[]={min1,max1};
    float r2[]={min2,max2};
    //这里必须为const不然后面calcHist提示参数不匹配——按理说非const实参是兼容const形参的，因为const形参仅仅是函数作出的一种承诺,承诺不改变该形参的值,而非const实参本身就可改变可不改变
    //应该完全可以作为const形参的实参，应该是const实参不兼容非const形参(因为函数不保证不改变形参值,而实参却要求这样的保证),而不是非const实参不兼容const形参,真是让人头大
    const float *ranges[]={r1,r2};
    cv::Mat *dst=new cv::Mat();
    cv::Mat *binsMat=new cv::Mat();
    if(channels==1){
        binsMat->create(1,bins1,CV_64FC1);
        double step=(max1-min1)/bins1;
        double *p=binsMat->ptr<double>(0);
        for(int i=0;i<bins1;++i){
            p[i]=min1+step*(i+binsShift*0.5);
        }
    }
    else{
        binsMat->create(bins1,bins2,CV_64FC2);
        double step1=(max1-min1)/bins1;
        double step2=(max2-min2)/bins2;
        for(int i=0;i<bins1;++i){
            cv::Vec2d *p=binsMat->ptr<cv::Vec2d>(i);
            for(int j=0;j<bins2;++j){
                p[j][0]=min1+step1*(i+binsShift*0.5);
                p[j][1]=min2+step2*(j+binsShift*0.5);
            }
        }
    }
    setProgress(10);
    int pro=100;
    if(accumulate)pro-=30;
    if(norm)pro-=20;
    cv::calcHist(&src,1,chans,cv::Mat(),*dst,channels,histSize,ranges,true,false);//这他妈哪个参数不匹配!!!Fuck U！
    setProgress(pro);
    if(accumulate){//累计密度
        int cur=pro;
        cv::Mat rowVec(1,dst->cols,dst->type());
        cv::Mat colVec(dst->rows,1,dst->type());
        dst->row(0).copyTo(rowVec);
        dst->col(0).copyTo(colVec);
        for(int i=1;i<dst->rows;++i){//每行叠加一次
            rowVec=rowVec+dst->row(i);
            rowVec.copyTo(dst->row(i));
            int prog=int(float(i)/dst->rows*15+cur);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        for(int i=1;i<dst->cols;++i){//每列叠加一次
            colVec=colVec+dst->col(i);
            colVec.copyTo(dst->col(i));
            int prog=int(float(i)/dst->cols*15+15+cur);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
    }
    if(norm){//归一化
        double maxVal=0;
        cv::minMaxLoc(*dst,new double(),&maxVal);
        (*dst)=(*dst)/maxVal;
        pro+=20;
        setProgress(pro);
    }
    setProgress(100);
    std::vector<Any> outs;
    outs.push_back(Any(*binsMat));
    outs.push_back(Any(*dst));
    setOutputs(outs,std::vector<int>(2,1));
}

void Histogram::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    for(int i=0;i<2;++i){
        if(targets[i]){
            Any(outputVars[i]).clean<cv::Mat>();
        }
    }
}

QWidget *Histogram::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string Histogram::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool Histogram::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string Histogram::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "calculate the histogram of an image";
}

std::vector<std::string> Histogram::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("input image to be calculated");
    
    return info;
}

std::vector<std::string> Histogram::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
    info.push_back("the bins of calculated histogram");
	info.push_back("the calculated histogram");

    return info;
}
