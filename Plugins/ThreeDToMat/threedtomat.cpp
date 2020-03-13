#include "threedtomat.h"
#include <string>
#include <QObject>
#include <opencv2/opencv.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

ThreeDToMat::ThreeDToMat()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new ThreeDToMatWidget();
    this->GSD=1;
    mode=0;
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->initParameters(this->GSD,this->mode);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&ThreeDToMatWidget::internalArgsChanged,[=](double GSD,int mode){
        this->GSD=GSD;
        this->mode=mode;
        requestInputs();
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int ThreeDToMat::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> ThreeDToMat::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("null");
    
    return inputTypes;
}

int ThreeDToMat::getOutputCount()
{
    //这里设置输出参数个数
    return 3;
}

std::vector<std::string> ThreeDToMat::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
    outputTypes.push_back("double");
    outputTypes.push_back("double");
	outputTypes.push_back("class cv::Mat");
    
    return outputTypes;
}


void ThreeDToMat::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    if(m_inputs.size()!=1||Any(m_inputs[0]).isNull()){
        return;
    }
    if(std::string(Any(m_inputs[0]).getType())=="class pcl::PointCloud<struct pcl::PointXYZRGB>"){
        pcl::PointCloud<pcl::PointXYZRGB> *cloud=&(Any(m_inputs[0]).getData<pcl::PointCloud<pcl::PointXYZRGB> >());
        if(cloud->size()==0){
            return;
        }
        int pro=0;
        setProgress(pro);
        double *min_x=new double(0);
        double *min_y=new double(0);
        double max_x,max_y;
        double min_z,max_z;
        //查找边界
        *min_x=cloud->at(0).x;
        *min_y=cloud->at(0).y;
        max_x=cloud->at(0).x;
        max_y=cloud->at(0).y;
        min_z=cloud->at(0).z;
        max_z=cloud->at(0).z;
        for(int i=0;i<cloud->size();++i){
            *min_x=*min_x>cloud->at(i).x?cloud->at(i).x:*min_x;
            *min_y=*min_y>cloud->at(i).y?cloud->at(i).y:*min_y;
            max_x=max_x<cloud->at(i).x?cloud->at(i).x:max_x;
            max_y=max_y<cloud->at(i).y?cloud->at(i).y:max_y;
            min_z=min_z>cloud->at(i).z?cloud->at(i).z:min_z;
            max_z=max_z<cloud->at(i).z?cloud->at(i).z:max_z;
            int prog=(int)(float(i)/cloud->size()*33);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        //划分网格投影
        if(this->GSD<=0){
            throw std::invalid_argument("parameter GSD illegal! GSD should be greater than 0");
        }
        int length=ceil((max_x-*min_x)/this->GSD);
        int width=ceil((max_y-*min_y)/this->GSD);
        cv::Mat *matOut=new cv::Mat();
        *matOut=cv::Mat::zeros(length,width,CV_32SC1);
        cv::Mat matLow;
        matLow=cv::Mat(length,width,CV_32FC1,cv::Scalar::all(max_z+1));//即每个元素为double型,单通道
        cv::Mat matTop;
        matTop=cv::Mat(length,width,CV_32FC1,cv::Scalar::all(min_z-1));
        for(int i=0;i<cloud->size();++i){
            int x=(int)((cloud->at(i).x-*min_x)/this->GSD);
            int y=(int)((cloud->at(i).y-*min_y)/this->GSD);
            if(mode==0){//点数
                matOut->at<int>(x,y)+=1;
            }
            else if(mode==1){
                matLow.at<float>(x,y)=matLow.at<float>(x,y)>cloud->at(i).z?cloud->at(i).z:matLow.at<float>(x,y);
                matTop.at<float>(x,y)=matTop.at<float>(x,y)<cloud->at(i).z?cloud->at(i).z:matTop.at<float>(x,y);
            }
            int factor=66;
            if(mode==1){//高差
                factor=33;
            }
            int prog=(int)(float(i)/cloud->size()*factor)+33;
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        std::vector<Any> outs;
        outs.push_back(Any(*min_x));
        outs.push_back(Any(*min_y));
        outs.push_back(Any());
        if(this->mode==0){
            outs[2].setData(*matOut);
            setProgress(100);
        }
        else if(this->mode==1){
            delete matOut;//不需要matOut要删除,以免内存泄漏
            cv::Mat *matDiff=new cv::Mat();
            *matDiff=cv::Mat(length,width,CV_32FC1,cv::Scalar::all(0));
            for(int i=0;i<matDiff->rows;++i){
                for(int j=0;j<matDiff->cols;++j){
                    matDiff->at<float>(i,j)=matTop.at<float>(i,j)-matLow.at<float>(i,j);
                    if(matDiff->at<float>(i,j)<0){
                        matDiff->at<float>(i,j)=0;
                    }
                }
                int prog=(int)(float(i)/(matTop.rows*matTop.cols)*33)+66;
                if(prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
            }
            outs[2].setData(*matDiff);
            setProgress(100);
        }
        setOutputs(outs,std::vector<int>(3,1));
    }
    if(std::string(Any(m_inputs[0]).getType())=="class pcl::PointCloud<struct pcl::PointXYZ>"){
        pcl::PointCloud<pcl::PointXYZ> *cloud=&(Any(m_inputs[0]).getData<pcl::PointCloud<pcl::PointXYZ> >());
        if(cloud->size()==0){
            return;
        }
        int pro=0;
        setProgress(pro);
        double *min_x=new double(0);
        double *min_y=new double(0);
        double max_x,max_y;
        double min_z,max_z;
        //查找边界
        *min_x=cloud->at(0).x;
        *min_y=cloud->at(0).y;
        max_x=cloud->at(0).x;
        max_y=cloud->at(0).y;
        min_z=cloud->at(0).z;
        max_z=cloud->at(0).z;
        for(int i=0;i<cloud->size();++i){
            *min_x=*min_x>cloud->at(i).x?cloud->at(i).x:*min_x;
            *min_y=*min_y>cloud->at(i).y?cloud->at(i).y:*min_y;
            max_x=max_x<cloud->at(i).x?cloud->at(i).x:max_x;
            max_y=max_y<cloud->at(i).y?cloud->at(i).y:max_y;
            min_z=min_z>cloud->at(i).z?cloud->at(i).z:min_z;
            max_z=max_z<cloud->at(i).z?cloud->at(i).z:max_z;
            int prog=(int)(float(i)/cloud->size()*33);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        //划分网格投影
        if(this->GSD<=0){
            throw std::invalid_argument("parameter GSD illegal! GSD should be greater than 0");
        }
        int length=ceil((max_x-*min_x)/this->GSD);
        int width=ceil((max_y-*min_y)/this->GSD);
        cv::Mat *matOut=new cv::Mat();
        *matOut=cv::Mat::zeros(length,width,CV_32SC1);
        cv::Mat matLow;
        matLow=cv::Mat(length,width,CV_32FC1,cv::Scalar::all(max_z+1));//即每个元素为double型,单通道
        cv::Mat matTop;
        matTop=cv::Mat(length,width,CV_32FC1,cv::Scalar::all(min_z-1));
        for(int i=0;i<cloud->size();++i){
            int x=(int)((cloud->at(i).x-*min_x)/this->GSD);
            int y=(int)((cloud->at(i).y-*min_y)/this->GSD);
            if(mode==0){//点数
                matOut->at<int>(x,y)+=1;
            }
            else if(mode==1){
                matLow.at<float>(x,y)=matLow.at<float>(x,y)>cloud->at(i).z?cloud->at(i).z:matLow.at<float>(x,y);
                matTop.at<float>(x,y)=matTop.at<float>(x,y)<cloud->at(i).z?cloud->at(i).z:matTop.at<float>(x,y);
            }
            int factor=66;
            if(mode==1){//高差
                factor=33;
            }
            int prog=(int)(float(i)/cloud->size()*factor)+33;
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        std::vector<Any> outs;
        outs.push_back(Any(*min_x));
        outs.push_back(Any(*min_y));
        outs.push_back(Any());
        if(this->mode==0){
            outs[2].setData(*matOut);
            setProgress(100);
        }
        else if(this->mode==1){
            delete matOut;//不需要matOut要删除,以免内存泄漏
            cv::Mat *matDiff=new cv::Mat();
            *matDiff=cv::Mat(length,width,CV_32FC1,cv::Scalar::all(0));
            for(int i=0;i<matDiff->rows;++i){
                for(int j=0;j<matDiff->cols;++j){
                    matDiff->at<float>(i,j)=matTop.at<float>(i,j)-matLow.at<float>(i,j);
                    if(matDiff->at<float>(i,j)<0){
                        matDiff->at<float>(i,j)=0;
                    }
                }
                int prog=(int)(float(i)/(matTop.rows*matTop.cols)*33)+66;
                if(prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
            }
            outs[2].setData(*matDiff);
            setProgress(100);
        }
        setOutputs(outs,std::vector<int>(3,1));
    }
}

void ThreeDToMat::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    for(int i=0;i<2;++i){
        if(targets[i])outputVars[i].clean<double>();
    }
    if(targets[2])outputVars[2].clean<cv::Mat>();
}

QWidget *ThreeDToMat::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string ThreeDToMat::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool ThreeDToMat::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string ThreeDToMat::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "project a point cloud to XY 2D plane";
}

std::vector<std::string> ThreeDToMat::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("point cloud whose point type is XYZ or XYZRGB");
    
    return info;
}

std::vector<std::string> ThreeDToMat::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
    info.push_back("x coordinate translation (minimum x coordinate)");
    info.push_back("y coordinate translation (minimum y coordinate)");
	info.push_back("output projection image");
    
    return info;
}
