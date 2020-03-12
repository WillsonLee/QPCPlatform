#include "pcdisplaythread.h"
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/shared_ptr.hpp>
#include <algorithm>
#include <random>
#include <QTime>
#include <QDebug>

PCDisplayThread::PCDisplayThread()
{

}

void PCDisplayThread::setCloud(Any data)
{
    this->data=data;
}

void PCDisplayThread::run()
{
    if(std::string(data.getType())=="class pcl::PointCloud<struct pcl::PointXYZ>"){
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud=pcl::PointCloud<pcl::PointXYZ>::Ptr(
                    &(data.getData<pcl::PointCloud<pcl::PointXYZ> >()),[](pcl::PointCloud<pcl::PointXYZ>*){});
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer);
        viewer->addPointCloud(cloud,"cloud");
        viewer->setPosition(0,0);//这狗屁PCLVisualizer根本没法用setCameraPosition设置位置,反倒是这个设置屏幕位置能起到居中显示点云功能
        viewer->setShowFPS(false);
        QString info="total points:"+QString::number(cloud->size())+"\npoint type:XYZ";
        viewer->addText(info.toStdString(),0,0,10,1,1,1,"cloud");
        while(!viewer->wasStopped()){
            viewer->spinOnce(100);
//            boost::this_thread::sleep(boost::posix_time::microseconds(100000));
        }
    }
    else if(std::string(data.getType())=="class pcl::PointCloud<struct pcl::PointXYZRGB>"){
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud=pcl::PointCloud<pcl::PointXYZRGB>::Ptr(
                    &(data.getData<pcl::PointCloud<pcl::PointXYZRGB> >()),[](pcl::PointCloud<pcl::PointXYZRGB>*){});
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer);
        viewer->addPointCloud(cloud,"cloud");
        viewer->setPosition(0,0);
        viewer->setShowFPS(false);
        QString info="total points:"+QString::number(cloud->size())+"\npoint type:XYZRGB";
        viewer->addText(info.toStdString(),0,0,10,1,1,1,"cloud");
        while(!viewer->wasStopped()){
            viewer->spinOnce(100);
//            boost::this_thread::sleep(boost::posix_time::microseconds(100000));
        }
    }
    else if(std::string(data.getType())==std::string(typeid(pcl::PointCloud<pcl::PointXYZ>::CloudVectorType).name())){
        pcl::PointCloud<pcl::PointXYZ>::CloudVectorType &vecPC=data.getData<pcl::PointCloud<pcl::PointXYZ>::CloudVectorType>();
        pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer);
        qsrand(QTime::currentTime().msec());
        int count=0;
        for(int i=0;i<vecPC.size();++i){
            cloud=pcl::PointCloud<pcl::PointXYZ>::Ptr(&vecPC.at(i),[](pcl::PointCloud<pcl::PointXYZ>*){});
            QString name=QString::number(i);
            viewer->addPointCloud(cloud,name.toStdString());
            float r=(float)qrand()/RAND_MAX;
            float g=(float)qrand()/RAND_MAX;
            float b=(float)qrand()/RAND_MAX;
            while(r<0.5&&g<0.5&&b<0.5){//保持为较亮颜色
                r=(float)qrand()/RAND_MAX;
                g=(float)qrand()/RAND_MAX;
                b=(float)qrand()/RAND_MAX;
            }
            viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR,r,g,b,name.toStdString());
            count+=cloud->size();
        }
        viewer->setPosition(0,0);
        viewer->setShowFPS(false);
        QString info="total points:"+QString::number(count)+"\ncluster size:"+QString::number(vecPC.size())+"\npoint type:XYZ";
        viewer->addText(info.toStdString(),0,0,10,1,1,1);
        while(!viewer->wasStopped()){
            viewer->spinOnce(100);
        }
    }
    else if(std::string(data.getType())==std::string(typeid(pcl::PointCloud<pcl::PointXYZRGB>::CloudVectorType).name())){
        pcl::PointCloud<pcl::PointXYZRGB>::CloudVectorType &vecPC=data.getData<pcl::PointCloud<pcl::PointXYZRGB>::CloudVectorType>();
        pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud;
        boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer);
        qsrand(QTime::currentTime().msec());
        int count=0;
        for(int i=0;i<vecPC.size();++i){
            cloud=pcl::PointCloud<pcl::PointXYZRGB>::Ptr(&vecPC.at(i),[](pcl::PointCloud<pcl::PointXYZRGB>*){});
            QString name=QString::number(i);
            viewer->addPointCloud(cloud,name.toStdString());
            float r=(float)qrand()/RAND_MAX;
            float g=(float)qrand()/RAND_MAX;
            float b=(float)qrand()/RAND_MAX;
            while(r<0.5&&g<0.5&&b<0.5){//保持为较亮颜色
                r=(float)qrand()/RAND_MAX;
                g=(float)qrand()/RAND_MAX;
                b=(float)qrand()/RAND_MAX;
            }
            viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_COLOR,r,g,b,name.toStdString());
            count+=cloud->size();
        }
        viewer->setPosition(0,0);
        viewer->setShowFPS(false);
        QString info="total points:"+QString::number(count)+"\ncluster size:"+QString::number(vecPC.size())+"\npoint type:XYZRGB";
        viewer->addText(info.toStdString(),0,0,10,1,1,1);
        while(!viewer->wasStopped()){
            viewer->spinOnce(100);
        }
    }
}
