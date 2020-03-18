#include "minboundingbox.h"
#include <string>
#include <QObject>
#include <opencv2/opencv.hpp>
#include <QMap>
#include <QDebug>

MinBoundingBox::MinBoundingBox()
{
    //这里执行内容为:
    //1.内部参数与图形界面初始化
    pluginWidget=new MinBoundingBoxWidget();
    binary=true;
    merge=true;
    node=1;
    //2.图形界面上的可设置参数初始化为内部参数的初始值(比如在pluginWidget里定义一个init(args...)函数来初始化
    pluginWidget->initArgs(binary,merge,node);
    //3.使插件监听图形界面上设置参数的变化(比如在pluginWidget里定义一个parasChanged信号)
    //  使用QObject::connect函数,将其connect到该插件上
    QObject::connect(pluginWidget,&MinBoundingBoxWidget::internalArgsChanged,[=](bool binary,bool merge,int node){
        this->binary=binary;
        this->merge=merge;
        this->node=node;
        this->requestInputs();
    });
    //4.设置插件的图形界面是内嵌式还是二级窗口式
    embededWidget=false;

}

int MinBoundingBox::getInputCount()
{
    //这里设置插件的输入参数个数
    return 1;
}

std::vector<std::string> MinBoundingBox::getInputTypes()
{
    std::vector<std::string> inputTypes;
    //这里设置输入参数的类型,inputTypes数组大小与getInputCount必须一致
	inputTypes.push_back("cv::Mat");
    
    return inputTypes;
}

int MinBoundingBox::getOutputCount()
{
    //这里设置输出参数个数
    return 3;
}

std::vector<std::string> MinBoundingBox::getOutputTypes()
{
    std::vector<std::string> outputTypes;
    //这里设置输出参数的类型,outputTypes数组大小与getOutputCount必须一致
	outputTypes.push_back("cv::Mat");
    outputTypes.push_back("std::vector<cv::RotatedRect,std::allocator<cv::RotatedRect> >");
    outputTypes.push_back("cv::Mat");
    
    return outputTypes;
}


void MinBoundingBox::run()
{
    //这里是实现插件功能的主体,一般有几件事需要执行:
    //1.使用setProgress来设置进度(有些任务比较耗时,没有进度不太人性化);一开始设为0,最后设为100以及-1(-1表示隐藏进度栏)
    //2.通过Any的数组m_inputs访问输入参数(如果有的话)
    //3.实现主要功能,在堆上开辟内存保存输出参数实际数据,用一个Any类型的std::vector保存输出参数
    //4.调用setOutputs函数通知外界输出参数更新了
    cv::Mat src=Any(m_inputs[0]).getData<cv::Mat>();
    if(src.type()!=CV_8UC1&&src.type()!=CV_16UC1&&src.type()!=CV_16SC1&&src.type()!=CV_32SC1&&src.type()!=CV_32FC1&&src.type()!=CV_64FC1){
        throw std::invalid_argument("MinBoundingBox plugin only support single channel image of type 8UC1,16UC1,16SC1,32SC1,32FC1 or 64FC1!");
    }
    setProgress(0);
    cv::Mat sigMat;
    src.convertTo(sigMat,CV_8UC1);
    setProgress(5);
    cv::Mat singles[3]={sigMat,sigMat.clone(),sigMat.clone()};
    setProgress(10);
    cv::Mat *display=new cv::Mat(src.rows,src.cols,CV_8UC3);//第一个输出参数
    cv::merge(singles,3,*display);
    setProgress(15);
    auto access=[&](int row,int col)->int{
        switch (src.depth()) {
        case CV_8U:
            return int(src.at<uchar>(row,col));
        case CV_16U:
            return int(src.at<ushort>(row,col));
        case CV_16S:
            return int(src.at<short>(row,col));
        case CV_32S:
            return src.at<int>(row,col);
        case CV_32F:
            return int(src.at<float>(row,col));
        case CV_64F:
            return int(src.at<double>(row,col));
        default:
            return 0;
        }
    };
    auto drawRect=[](cv::Mat &src,cv::RotatedRect rect){
        cv::Point2f vertex[4];
        rect.points(vertex);
        for(int i=0;i<4;++i){
            cv::line(src,vertex[i],vertex[(i+1)%4],cv::Scalar(0,0,255),3,cv::LINE_AA);
        }
    };
    auto withinRect=[](cv::RotatedRect rect,cv::Point2f p)->int{
        cv::Point2f points[4];
        rect.points(points);//points顺序为顺时针bottomLeft->topLeft->topRight->bottomRight
        cv::Vec2f v21=points[0]-points[1];
        cv::Vec2f v23=points[2]-points[1];
        cv::Vec2f v43=points[2]-points[3];
        cv::Vec2f v41=points[0]-points[3];
        cv::Vec2f v2=p-points[1];
        cv::Vec2f v4=p-points[3];
        float dot1=v2.dot(v21);
        float dot2=v2.dot(v23);
        float dot3=v4.dot(v43);
        float dot4=v4.dot(v41);
        if(dot1>0&&dot2>0&&dot3>0&&dot4>0)return 1;
        auto cross=[](cv::Vec2f &v1,cv::Vec2f &v2)->float{return v1[0]*v2[1]-v2[0]*v1[1];};
        if(cross(v2,v21)==0&&v2.dot(cv::Vec2f(p-points[0]))<=0)return 0;
        if(cross(v2,v23)==0&&v2.dot(cv::Vec2f(p-points[2]))<=0)return 0;
        if(cross(v4,v43)==0&&v4.dot(cv::Vec2f(p-points[2]))<=0)return 0;
        if(cross(v4,v41)==0&&v4.dot(cv::Vec2f(p-points[0]))<=0)return 0;
        return -1;
    };
    if(binary){
        int pro=15;
        std::vector<cv::Point> points;
        for(int i=0;i<src.rows;++i){
            for(int j=0;j<src.cols;++j){
                if(access(i,j)!=0){
                    points.push_back(cv::Point(j,i));
                }
            }
            int prog=int(float(i)/src.rows*40+15);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        cv::RotatedRect rect=cv::minAreaRect(points);
        drawRect(*display,rect);
        std::vector<cv::RotatedRect> *vecOut=new std::vector<cv::RotatedRect>(1,rect);//第二个输出
        cv::Mat *mask=new cv::Mat();//第三个输出
        *mask=cv::Mat::zeros(src.rows,src.cols,CV_8UC1);
        for(int i=0;i<mask->rows;++i){
            for(int j=0;j<mask->cols;++j){
                if(withinRect(rect,cv::Point2f(j,i))>=0){
                    mask->at<uchar>(i,j)=255;
                }
            }
            int prog=int(float(i)/mask->rows*45+55);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        setProgress(100);
        std::vector<Any> outs;
        outs.push_back(Any(*display));
        outs.push_back(Any(*vecOut));
        outs.push_back(Any(*mask));
        setOutputs(outs,std::vector<int>(3,1));
    }
    else{
        int pro=15;
        setProgress(pro);
        std::vector<cv::RotatedRect> *vecOut=new std::vector<cv::RotatedRect>();//第二个输出
        cv::Mat *mask=new cv::Mat();//第三个输出
        *mask=cv::Mat::zeros(src.rows,src.cols,CV_32SC1);
        QMap<int,std::vector<cv::Point> > labelAndPoints;
        QMap<int,cv::RotatedRect> labelAndRects;
        for(int i=0;i<src.rows;++i){
            for(int j=0;j<src.cols;++j){
                int label=access(i,j);
                if(label!=0){
                    if(!labelAndPoints.contains(label)){
                        labelAndPoints[label]=std::vector<cv::Point>();
                        labelAndRects[label]=cv::RotatedRect();
                    }
                    labelAndPoints[label].push_back(cv::Point(j,i));
                }
            }
            int prog=int(float(i)/src.rows*10+15);
            if(prog>pro){
                pro=prog;
                setProgress(pro);
            }
        }
        setProgress(25);
        cv::parallel_for_(cv::Range(0,labelAndPoints.size()),[&](const cv::Range &range){
            for(int r=range.start;r<range.end;++r){
                int label=labelAndPoints.keys().at(r);
                labelAndRects[label]=cv::minAreaRect(labelAndPoints[label]);
                int prog=int(float(r)/(range.end-range.start)*15+25);
                if(prog<=40&&prog>pro){
                    pro=prog;
                    setProgress(pro);
                }
            }
        });
        setProgress(40);
        QList<int> keys=labelAndRects.keys();
        std::sort(keys.begin(),keys.end());
        setProgress(50);
        if(merge){//需要合并重叠区块
            int incre=int(float(1)/labelAndRects.size()*30);
            auto rectOverlap=[&](cv::RotatedRect rect1,cv::RotatedRect rect2)->bool{
                cv::Point2f pts1[4];
                cv::Point2f pts2[4];
                rect1.points(pts1);
                rect2.points(pts2);
                int count1=0,count2=0;
                for(int i=0;i<4;++i)withinRect(rect2,pts1[i])>=0?count1++:count1;
                for(int i=0;i<4;++i)withinRect(rect1,pts2[i])>=0?count2++:count2;
                if(count1>=node||count2>=node)return true;
//                if(withinRect(rect2,pts1[0])>=0||withinRect(rect2,pts1[1])>=0||withinRect(rect2,pts1[2])>=0||withinRect(rect2,pts1[3])>=0)return true;
//                if(withinRect(rect1,pts2[0])>=0||withinRect(rect1,pts2[1])>=0||withinRect(rect1,pts2[2])>=0||withinRect(rect1,pts2[3])>=0)return true;
                return false;
            };
            auto overlapExists=[&](bool &exist,int &lb1,int &lb2){
                exist=false;
                for(int i=0;i<keys.size();++i){
                    for(int j=0;j<keys.size();++j){
                        lb1=keys[i];
                        lb2=keys[j];
                        if(i!=j&&lb1!=lb2&&rectOverlap(labelAndRects[lb1],labelAndRects[lb2])){
                            exist=true;
//                            qDebug()<<"i="<<i<<",j="<<j<<"lb1="<<lb1<<",lb2="<<lb2<<",exists="<<exist<<endl;
//                            break;//这里break不够只能跳出一层循环,目标是直接跳出两层循环;初级错误!
                            return;
                        }
                    }
                }
            };
//            int outCount=0;//test variable
            auto mergeOverlap=[&](int lb1,int lb2){
                int minLabel=lb1<lb2?lb1:lb2;
                int maxLabel=lb1>lb2?lb1:lb2;
                labelAndPoints[minLabel].insert(labelAndPoints[minLabel].end(),labelAndPoints[maxLabel].begin(),labelAndPoints[maxLabel].end());
                labelAndRects[minLabel]=cv::minAreaRect(labelAndPoints[minLabel]);
                labelAndPoints.remove(maxLabel);
                labelAndRects.remove(maxLabel);
                keys.removeOne(maxLabel);
                //test
//                cv::Mat state(display->rows,display->cols,CV_8UC3,cv::Scalar::all(0));
//                for(int i=0;i<keys.size();++i){
//                    drawRect(state,labelAndRects[keys.at(i)]);
//                }
//                cv::imwrite("D:/workdir/temp/state_"+QString::number(outCount).toStdString()+".png",state);
//                outCount++;
            };
            int lb1,lb2;
            bool exist;
            overlapExists(exist,lb1,lb2);
            while(exist){
                mergeOverlap(lb1,lb2);
                overlapExists(exist,lb1,lb2);
                if(pro<80){
                    pro+=incre;
                    setProgress(pro);
                }
            }
            pro=80;
            setProgress(pro);
        }
        for(int key:keys){
            vecOut->push_back(labelAndRects[key]);
        }
        setProgress(86);
        cv::parallel_for_(cv::Range(0,keys.size()),[&](const cv::Range &range){
            for(int r=range.start;r<range.end;++r){
                drawRect(*display,labelAndRects[keys[r]]);
            }
        });
        setProgress(93);
        cv::parallel_for_(cv::Range(0,mask->rows*mask->cols),[&](const cv::Range &range){
            for(int r=range.start;r<range.end;++r){
                int y=r/mask->cols;//行
                int x=r%mask->cols;//列
                auto ans=std::find_if(keys.begin(),keys.end(),[&](int label){return withinRect(labelAndRects[label],cv::Point2f(x,y))>=0;});
                if(ans!=keys.end()){
                    mask->at<int>(y,x)=*ans;
                }
            }
        });
        setProgress(100);
        std::vector<Any> outs;
        outs.push_back(Any(*display));
        outs.push_back(Any(*vecOut));
        outs.push_back(Any(*mask));
        setOutputs(outs,std::vector<int>(3,1));
    }
}

void MinBoundingBox::cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets)
{
    //这里实现插件的垃圾清理功能,因为外界不知道插件使用的参数类型与输出结果数据的类型
    //只能交由插件执行该功能,比如输出参数为一个double型与一个std::string型,可以如下(相应的target指明是否需要清理):
    //if(targets[0])outputVars[0].clean<double>();
    //if(targets[1])outputVars[1].clean<std::string>();
    if(targets[0])Any(outputVars[0]).clean<cv::Mat>();
    if(targets[1])Any(outputVars[1]).clean<std::vector<cv::RotatedRect> >();
    if(targets[2])Any(outputVars[2]).clean<cv::Mat>();
}

QWidget *MinBoundingBox::getWidget()
{
    //这里设置是否有图形界面,假如插件不需要嵌入式的图形界面或者弹出的二级窗口,这里返回NULL;否则返回pluginWidget
    return pluginWidget;
}

std::string MinBoundingBox::saveState()
{
    //该函数用于保存该插件内部参数,返回的字符串必须为类似xml标签式的信息,这些信息可以指定数据文件存放位置等信息,这些格式信息可被主程序
	//作为xml文档的一部分保存,比如返回字符串"<data>D:/workdir</data>"表示中间某个处理结果数据保存位置为D:/workdir,具体的解译方式由插件自己确定
    return "";
}

bool MinBoundingBox::restoreState(std::string stateFile)
{
    //该函数用于解析saveState保存的文件,从而从文件中完全恢复插件状态;返回值表示恢复成功与否
    return false;
}

std::string MinBoundingBox::getDoc()
{
    //该函数获取该插件的文档,返回一个文档的字符串
    return "get the minimum bounding box of a single channel image";
}

std::vector<std::string> MinBoundingBox::getInputInfo()
{
    //该函数给出每个参数介绍,返回各个参数的介绍字符串,可以与输入参数数量不一但是顺序必须相同
    std::vector<std::string> info;
    //添加描述
    info.push_back("single channel image of type 8U||16U||16S||32S||32F||64F (Note that the data type 32F and 64F will be rounded to int by force cast!)");
    
    return info;
}

std::vector<std::string> MinBoundingBox::getOutputInfo()
{
    //该函数获取输出参数信息
    std::vector<std::string> info;
    //添加描述
	info.push_back("original image and bounding rects");
    info.push_back("the geometry of the resulted MBB");
    info.push_back("MBB mask image (multi-label supported)");
    
    return info;
}
