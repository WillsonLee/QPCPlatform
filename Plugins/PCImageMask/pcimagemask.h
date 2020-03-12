#ifndef PCIMAGEMASK_H
#define PCIMAGEMASK_H

#include "pcimagemask_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <pcimagemaskwidget.h>
#include <opencv2/opencv.hpp>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <QDebug>

class PCIMAGEMASKSHARED_EXPORT PCImageMask:public IPlugin
{
public:
    PCImageMask();

    // IPlugin interface
public:
    int getInputCount();
    std::vector<std::string> getInputTypes();
    int getOutputCount();
    std::vector<std::string> getOutputTypes();
    void run();
    void cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets);
    QWidget *getWidget();
    std::string saveState();
    bool restoreState(std::string stateFile);
    std::string getDoc();
    std::vector<std::string> getInputInfo();
    std::vector<std::string> getOutputInfo();
private:
    //定义内部参数
    PCImageMaskWidget *pluginWidget;
    double x,y,gsd;
    bool autoOffset,autoGSD;
    bool binary;
    bool inversedMask;
    template<class PointT>
    void determineXYGsd(const pcl::PointCloud<PointT> &cloud,const cv::Mat &src,int prog1,int prog2)
    {
        int pro=prog1;
        setProgress(pro);
        if(autoOffset||autoGSD){
            double min_x=cloud.at(0).x;
            double min_y=cloud.at(0).y;
            double max_x=min_x;
            double max_y=min_y;
            int scale=prog2-prog1;
            for(int i=1;i<cloud.size();++i){
                min_x=min_x>cloud.at(i).x?cloud.at(i).x:min_x;
                max_x=max_x<cloud.at(i).x?cloud.at(i).x:max_x;
                min_y=min_y>cloud.at(i).y?cloud.at(i).y:min_y;
                max_y=max_y<cloud.at(i).y?cloud.at(i).y:max_y;
                int prog=int(float(i)/cloud.size()*scale+prog1);
                if(prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
            }
            if(autoOffset){
                this->x=min_x;
                this->y=min_y;
            }
            if(autoGSD){
                double xGsd_min=(max_x-min_x)/src.rows;
                double xGsd_max=(max_x-min_x)/(src.rows-1);
                double yGsd_min=(max_y-min_y)/src.cols;
                double yGsd_max=(max_y-min_y)/(src.cols-1);
                double right=xGsd_max>yGsd_max?yGsd_max:xGsd_max;
                double left=xGsd_min<yGsd_min?yGsd_min:xGsd_min;
                if(left>right){
                    throw std::exception("the image GSD cannot be automatically determined!Either the image area is not the same with the point cloud or the image has different GSD in x and y direction");
                }
                else{
                    this->gsd=(left+right)/2;
                }
            }
            pluginWidget->setAutoParas(this->x,this->y,this->gsd);
        }
        setProgress(prog2);
    }
    template<class PointT>
    void extractOutput(const pcl::PointCloud<PointT> &cloud,const cv::Mat &src,Any &out,int prog1,int prog2)
    {
        int pro=prog1;
        setProgress(pro);
        pcl::PointCloud<PointT> *cloudOut=new pcl::PointCloud<PointT>();
        QMap<int,int> labels;
        int labelCount=0;
        //一定要先遍历一遍确定有多少个label然后直接生成一个这么大的vector而不能之后再push_back,会有什么Eigen的对齐问题,莫名其妙;
        //问题不在这里，而在于对齐，含有Eigen中类对象作为成员变量的类(比如这里的PointCloud)会有对齐的问题，生成其vector时要指定allocator
        pcl::PointCloud<PointT>::CloudVectorType *vecOut=new pcl::PointCloud<PointT>::CloudVectorType;
        int factor=prog2-prog1;
        int shift=prog1;
        int ptsCount=0;
        QMap<int,int> labelPtsNumber;
        auto accessMat=[](cv::Mat src,int x,int y)->int{
            if(src.type()==CV_8UC1)return (int)src.at<uchar>(x,y);
            else if(src.type()==CV_16UC1)return (int)src.at<ushort>(x,y);
            else if(src.type()==CV_32SC1) return src.at<int>(x,y);return 0;};
        for(int i=0;i<cloud.size();++i){
            int x=(int)((cloud.at(i).x-this->x)/this->gsd);
            int y=(int)((cloud.at(i).y-this->y)/this->gsd);
            if(0<=x&&x<src.rows&&0<=y&&y<src.cols){
                if(inversedMask){
                    if(accessMat(src,x,y)==0){
                        cloudOut->points.push_back(PointT(cloud.at(i)));
                        ptsCount++;
                    }
                }
                else if(binary){
                    if(accessMat(src,x,y)!=0){
                        cloudOut->points.push_back(PointT(cloud.at(i)));
                        ptsCount++;
                    }
                }
                else{
                    if(0<=x&&x<src.rows&&0<=y&&y<src.cols){
                        int label=0;
                        label=accessMat(src,x,y);
                        if(label!=0){
                            if(!labels.contains(label)){
                                labels[label]=labelCount++;
                                labelPtsNumber[label]=0;
                                vecOut->push_back(pcl::PointCloud<PointT>());
                            }
                            (*vecOut)[labels[label]].points.push_back(PointT(cloud.at(i)));//label对应的点云添加点
                            labelPtsNumber[label]+=1;
                        }
                    }
                }
            }
            int prog=int(float(i)/cloud.size()*factor+shift);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        if(inversedMask||binary){
            cloudOut->width=ptsCount;
            cloudOut->height=1;
            cloudOut->is_dense=true;
            delete vecOut;
            out.setData(*cloudOut);
        }
        else{
            for(auto key:labelPtsNumber.keys()){
                (*vecOut)[labels[key]].width=labelPtsNumber[key];
                (*vecOut)[labels[key]].height=1;
                (*vecOut)[labels[key]].is_dense=true;
            }
            delete cloudOut;
            out.setData(*vecOut);
        }
        setProgress(prog2);
    }
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(PCImageMask)
};
REGISTER_REFLEX(PCImageMask)

#endif // TESTPLUGIN_H
