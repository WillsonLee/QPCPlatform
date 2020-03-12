#include "morphology.h"
#include <string>
#include <QObject>

Morphology::Morphology()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new MorphologyWidget();
    allMorphTypes.push_back(cv::MORPH_ERODE);
    allMorphTypes.push_back(cv::MORPH_DILATE);
    allMorphTypes.push_back(cv::MORPH_OPEN);
    allMorphTypes.push_back(cv::MORPH_CLOSE);
    allMorphTypes.push_back(cv::MORPH_GRADIENT);
    allMorphTypes.push_back(cv::MORPH_TOPHAT);
    allMorphTypes.push_back(cv::MORPH_BLACKHAT);
    allMorphTypes.push_back(cv::MORPH_HITMISS);
    morphType=0;
    allShapes.push_back(cv::MORPH_RECT);
    allShapes.push_back(cv::MORPH_CROSS);
    allShapes.push_back(cv::MORPH_ELLIPSE);
    shape=0;
    allBorderTypes.push_back(cv::BORDER_CONSTANT);
    allBorderTypes.push_back(cv::BORDER_REPLICATE);
    allBorderTypes.push_back(cv::BORDER_REFLECT);
    allBorderTypes.push_back(cv::BORDER_WRAP);
    allBorderTypes.push_back(cv::BORDER_REFLECT_101);
    allBorderTypes.push_back(cv::BORDER_TRANSPARENT);
    allBorderTypes.push_back(cv::BORDER_ISOLATED);
    borderType=4;
    width=3;
    height=3;
    anchorX=-1;
    anchorY=-1;
    iter=1;
    borderValue=cv::Scalar::all(0);
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->initArgs(morphType,shape,width,height,anchorX,anchorY,iter,borderType,borderValue);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&MorphologyWidget::argsChanged,[=](int morphType,int shape,int width,int height,
                     int anchorX,int anchorY,int iter,int borderType,cv::Scalar borderValue){
        bool changed=false;
        checkAndChange(morphType,this->morphType,changed);
        checkAndChange(shape,this->shape,changed);
        checkAndChange(width,this->width,changed);
        checkAndChange(height,this->height,changed);
        checkAndChange(anchorX,this->anchorX,changed);
        checkAndChange(anchorY,this->anchorY,changed);
        checkAndChange(iter,this->iter,changed);
        checkAndChange(borderType,this->borderType,changed);
        bool allSame=true;
        for(int i=0;i<4;++i){allSame=allSame&&(this->borderValue[i]==borderValue[i]);}
        if(!allSame){
            this->borderValue=borderValue;
            changed=true;
        }
        if(changed){
            requestInputs();
        }
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int Morphology::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> Morphology::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("class cv::Mat");
    
    return inputTypes;
}

int Morphology::getOutputCount()
{
    //这里设置输出参数个数
    return 1;
}

std::vector<std::string> Morphology::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	outputTypes.push_back("class cv::Mat");
    
    return outputTypes;
}


void Morphology::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat src=Any(m_inputs[0]).getData<cv::Mat>();
    if(src.type()!=CV_8UC1&&allMorphTypes[morphType]==cv::MORPH_HITMISS){
        throw std::exception("morphology operation \"hit or miss\" only supported for CV_8UC1 binary images!");
    }
    if(src.depth()==CV_8U||src.depth()==CV_16U||src.depth()==CV_16S||src.depth()==CV_32S||src.depth()==CV_32F||src.depth()==CV_64F){
        cv::Mat *matOut=new cv::Mat();
        cv::Point anch=cv::Point(anchorX,anchorY);
        cv::Mat kernel=cv::getStructuringElement(allShapes[shape],cv::Size(width,height),anch);
        setProgress(20);
        bool needConvert=false;
        if(src.type()==CV_32SC(src.channels())){
            needConvert=true;
            src.convertTo(src,CV_32FC(src.channels()));//实际上32S型是不允许的,采取曲线方式先转为32F最后再转回来
        }
        cv::morphologyEx(src,*matOut,allMorphTypes[morphType],kernel,anch,iter,allBorderTypes[borderType],borderValue);
        if(needConvert){
            matOut->convertTo(*matOut,CV_32SC(matOut->channels()));
        }
        setProgress(90);
        setOutputs(std::vector<Any>(1,Any(*matOut)),std::vector<int>(1,1));
    }
    else{
        throw std::exception("image depth error!Morphology operations can only be applied to image with depth==CV_8U||CV_16U||CV_16S||CV_32S||CV_32F||CV_64F");
    }
}

void Morphology::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    if(targets[0])Any(outputVars[0]).clean<cv::Mat>();
}

QWidget *Morphology::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string Morphology::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool Morphology::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string Morphology::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "apply morphology operation to the input image";
}

std::vector<std::string> Morphology::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("opencv image to be operated");
    
    return info;
}

std::vector<std::string> Morphology::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	info.push_back("opencv image after mophology operation");
    
    return info;
}

void Morphology::checkAndChange(int src, int &dst, bool &changed)
{
    if(src!=dst){
        dst=src;
        changed=true;
    }
}
