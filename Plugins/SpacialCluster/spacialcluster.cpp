#include "spacialcluster.h"
#include <string>
#include <QObject>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/PointIndices.h>
#include <QDebug>

SpacialCluster::SpacialCluster()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new SpacialClusterWidget();
    tolAuto=true;
    tol=1;
    min_pts=200;
    max_pts=50000000;
    this->xyz=0;
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->setArgs(tolAuto,tol);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&SpacialClusterWidget::argsChanged,[=](bool tolAuto_,double tol_){
       bool changed=false;
       if(tolAuto_!=tolAuto){
           tolAuto=tolAuto_;
           changed=true;
       }
       if(tol_!=tol){
           tol=tol_;
           changed=true;
       }
       if(changed){
           requestInputs();
       }
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int SpacialCluster::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> SpacialCluster::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("null");
    
    return inputTypes;
}

int SpacialCluster::getOutputCount()
{
    //这里设置输出参数个数
    return 1;
}

std::vector<std::string> SpacialCluster::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	outputTypes.push_back("null");
    
    return outputTypes;
}


void SpacialCluster::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    if(std::string(Any(m_inputs[0]).getType())=="class pcl::PointCloud<struct pcl::PointXYZ>"){
        pcl::PointCloud<pcl::PointXYZ> *cloud=&(Any(m_inputs[0]).getData<pcl::PointCloud<pcl::PointXYZ> >());
        pcl::search::KdTree<pcl::PointXYZ>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZ>);
        int pro=0;
        setProgress(pro);
        if(this->tolAuto){
            int K=2;
            std::vector<float> all_dis(cloud->size(),0.0);
            pcl::PointXYZ searchP;
            std::vector<int> neighborIdx(K);
            std::vector<float> neighborDis(K);
            for(int i=0;i<cloud->size();++i){
                searchP=cloud->at(i);
                if(tree->nearestKSearch(searchP,K,neighborIdx,neighborDis)>0){
                    all_dis[i]=sqrt(neighborDis[1]);
                }
                int prog=int(float(i)/cloud->size()*20);
                if(prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
            }
            double ave_dis=0.0;
            double std_dis=0.0;
            int i=0;
            for(double dis:all_dis){
                ave_dis+=dis;
                int prog=int(float(i)/cloud->size()*20+20);
                if(prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
                i++;
            }
            ave_dis/=all_dis.size();
            i=0;
            for(double dis:all_dis){
                std_dis+=(dis-ave_dis)*(dis-ave_dis);
                int prog=int(float(i)/cloud->size()*40);
                if(prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
                i++;
            }
            std_dis/=all_dis.size();
            std_dis=sqrt(std_dis);
            this->tol=ave_dis+3*std_dis;
        }
        int factor=this->tolAuto?20:50;
        int shift=this->tolAuto?60:0;
        std::vector<pcl::PointIndices> cluster_indices;
        pcl::EuclideanClusterExtraction<pcl::PointXYZ> ec;
        ec.setClusterTolerance(this->tol);
        ec.setMinClusterSize(this->min_pts);
        ec.setMaxClusterSize(this->max_pts);
        ec.setSearchMethod(tree);
        boost::shared_ptr<pcl::PointCloud<pcl::PointXYZ> > cloud_ptr(cloud,[](pcl::PointCloud<pcl::PointXYZ> *){});
        ec.setInputCloud(cloud_ptr);
        ec.extract(cluster_indices);
        setProgress(80);
        pcl::PointCloud<pcl::PointXYZ>::CloudVectorType *outs(new pcl::PointCloud<pcl::PointXYZ>::CloudVectorType(cluster_indices.size()));
        pcl::ExtractIndices<pcl::PointXYZ> extract;
        extract.setInputCloud(cloud_ptr);
        for(int i=0;i<cluster_indices.size();++i){
            extract.setIndices(boost::make_shared<std::vector<int> >(cluster_indices[i].indices));
            extract.setNegative(false);
            extract.filter((*outs)[i]);
            int prog=int(float(i)/cloud->size()*factor+shift+20);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        setOutputs(std::vector<Any>(1,Any(*outs)),std::vector<int>(1,1));
        this->xyz=1;
    }
    else if(std::string(Any(m_inputs[0]).getType())=="class pcl::PointCloud<struct pcl::PointXYZRGB>"){
        pcl::PointCloud<pcl::PointXYZRGB> *cloud=&(Any(m_inputs[0]).getData<pcl::PointCloud<pcl::PointXYZRGB> >());
        pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree(new pcl::search::KdTree<pcl::PointXYZRGB>);
        boost::shared_ptr<pcl::PointCloud<pcl::PointXYZRGB> > cloud_ptr(cloud,[](pcl::PointCloud<pcl::PointXYZRGB>*){});
        tree->setInputCloud(cloud_ptr);
        int pro=0;
        setProgress(pro);
        if(this->tolAuto){
            int K=2;
            std::vector<float> all_dis(cloud->size(),0.0);
            pcl::PointXYZRGB searchP;
            std::vector<int> neighborIdx(K);
            std::vector<float> neighborDis(K);
            for(int i=0;i<cloud->size();++i){
                searchP=cloud->at(i);
                if(tree->nearestKSearch(searchP,K,neighborIdx,neighborDis)>0){
                    all_dis[i]=sqrt(neighborDis[1]);
                }
                int prog=int(float(i)/cloud->size()*20);
                if(prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
            }
            double ave_dis=0.0;
            double std_dis=0.0;
            int i=0;
            for(double dis:all_dis){
                ave_dis+=dis;
                int prog=int(float(i)/cloud->size()*20+20);
                if(prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
                i++;
            }
            ave_dis/=all_dis.size();
            i=0;
            for(double dis:all_dis){
                std_dis+=(dis-ave_dis)*(dis-ave_dis);
                int prog=int(float(i)/cloud->size()*20+40);
                if(prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
                i++;
            }
            std_dis/=all_dis.size();
            std_dis=sqrt(std_dis);
            this->tol=ave_dis+3*std_dis;
        }
        int factor=this->tolAuto?20:50;
        int shift=this->tolAuto?80:0;
        std::vector<pcl::PointIndices> cluster_indices;
        pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
        ec.setClusterTolerance(this->tol);
        ec.setMinClusterSize(this->min_pts);
        ec.setMaxClusterSize(this->max_pts);
        ec.setSearchMethod(tree);
        ec.setInputCloud(cloud_ptr);
        ec.extract(cluster_indices);
        if(this->tolAuto){
            setProgress(80);
        }
        else{
            setProgress(50);
        }
        pcl::PointCloud<pcl::PointXYZRGB>::CloudVectorType *outs(new pcl::PointCloud<pcl::PointXYZRGB>::CloudVectorType(cluster_indices.size()));
        pcl::ExtractIndices<pcl::PointXYZRGB> extract;
        extract.setInputCloud(cloud_ptr);
        for(int i=0;i<cluster_indices.size();++i){
            extract.setIndices(boost::make_shared<std::vector<int> >(cluster_indices[i].indices));
            extract.setNegative(false);
            extract.filter((*outs)[i]);
            int prog=int(float(i)/cloud->size()*factor+shift);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        setOutputs(std::vector<Any>(1,Any(*outs)),std::vector<int>(1,1));
        this->xyz=2;
    }
    else{
        throw std::exception("input type is not XYZ or XYZRGB type point cloud!");
    }
}

void SpacialCluster::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    if(this->xyz==1){
        if(targets[0])Any(outputVars[0]).clean<pcl::PointCloud<pcl::PointXYZ>::CloudVectorType>();
    }
    else if(this->xyz==2){
        if(targets[0])Any(outputVars[0]).clean<pcl::PointCloud<pcl::PointXYZRGB>::CloudVectorType>();
    }
}

QWidget *SpacialCluster::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string SpacialCluster::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool SpacialCluster::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string SpacialCluster::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "spacial clustering the point cloud";
}

std::vector<std::string> SpacialCluster::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
	info.push_back("input point whose point type is XYZ or XYZRGB");
    
    return info;
}

std::vector<std::string> SpacialCluster::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	info.push_back("vector of point cloud with same point type as input");
    
    return info;
}
