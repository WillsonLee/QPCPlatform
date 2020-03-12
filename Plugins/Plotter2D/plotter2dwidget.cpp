#include "plotter2dwidget.h"
#include "ui_plotter2dwidget.h"
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QInputDialog>
#include <QFileDialog>
#include <QDebug>

Plotter2DWidget::Plotter2DWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Plotter2DWidget)
{
    ui->setupUi(this);
    marker_size=8;
    connect(ui->customPlot,&QCustomPlot::mouseRelease,this,[=](QMouseEvent *event){
        if(event->button()==Qt::RightButton){
            this->showContext();
        }
        if(event->button()==Qt::LeftButton){
            //选中点输出
            QPoint pos=event->pos();
            double x=ui->customPlot->xAxis->pixelToCoord(pos.x());
            double y=ui->customPlot->yAxis->pixelToCoord(pos.y());
            QVector<int> index(this->x.size());
            for(int i=0;i<index.size();++i){
                index[i]=i;
            }
            QVector<double>::iterator x_iter=this->x.begin();
            QVector<double>::iterator y_iter=this->y.begin();
            auto dis_sqr=[=](int idx)->double{
                double x1=*(x_iter+idx);
                double y1=*(y_iter+idx);
                return (x1-x)*(x1-x)+(y1-y)*(y1-y);
            };
            QVector<int>::iterator iter=std::min_element(index.begin(),index.end(),[=](int idx1,int idx2)->bool{
                return dis_sqr(idx1)<dis_sqr(idx2);
            });
            auto getPixelDis=[=](int idx)->double{
                double scale_x=abs(ui->customPlot->xAxis->pixelToCoord(1)-ui->customPlot->xAxis->pixelToCoord(0));
                double scale_y=abs(ui->customPlot->yAxis->pixelToCoord(1)-ui->customPlot->yAxis->pixelToCoord(0));
                double dx=(*(x_iter+idx)-x)/scale_x;
                double dy=(*(y_iter+idx)-y)/scale_y;
                return dx*dx+dy*dy;
            };
            if(getPixelDis(*iter)<marker_size*marker_size){
                this->printMessage(QString("selected data point:(%1,%2)").arg(this->x[*iter]).arg(this->y[*iter]));
            }
        }
    });
    this->xLabel="x";
    this->yLabel="y";
    this->title="untitled";
    this->scatterPlot=true;
    this->linePlot=true;
    this->barPlot=false;
    this->enableInteraction=true;
    //test
//    QVector<double> x1(101);
//    QVector<double> y1(101);
//    for(int i=0;i<101;++i){
//        x1[i]=i;
//        y1[i]=pow(x1[i],0.3);
//    }
//    setData(x1,y1);
}

void Plotter2DWidget::setData(QVector<double> &x, QVector<double> &y)
{
    this->x=x;
    this->y=y;
    if(this->x.size()==0||this->y.size()==0){
        throw std::exception("no input data!");
    }
    else if(this->x.size()!=this->y.size()!=0){
        throw std::exception("dimensionality of input data x and y do not coincide!");
    }
    else{
       this->plotData();
    }
}

void Plotter2DWidget::onDataChange(QVariant x, QVariant y)
{
    //这个跟我的Any类一样,在发信号时用QVariant打包下数据,然后在槽函数中解包数据
    QVector<double> xData=x.value<QVector<double> >();
    QVector<double> yData=y.value<QVector<double> >();
    setData(xData,yData);
}

Plotter2DWidget::~Plotter2DWidget()
{
    delete ui;
}

void Plotter2DWidget::plotData()
{
    ui->customPlot->clearGraphs();
    ui->customPlot->clearPlottables();
    if(enableInteraction){
        ui->customPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);
    }
    if(this->scatterPlot){
        ui->customPlot->addGraph();
        int idx=ui->customPlot->graphCount()-1;
        ui->customPlot->graph(idx)->setData(x,y);
        ui->customPlot->graph(idx)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot->graph(idx)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,marker_size));
        ui->customPlot->graph(idx)->setSelectable(QCP::stDataRange);
    }
    if(this->linePlot){
        ui->customPlot->addGraph();
        int idx=ui->customPlot->graphCount()-1;
        ui->customPlot->graph(idx)->setData(this->x,this->y);
//        ui->customPlot->graph(idx)->setSelectable(QCP::stNone);
    }
    if(this->barPlot){
        QCPBars *bar=new QCPBars(ui->customPlot->xAxis,ui->customPlot->yAxis);
        bar->setData(this->x,this->y);
        bar->setSelectable(QCP::stNone);
    }
    ui->customPlot->xAxis->setLabel(this->xLabel);
    ui->customPlot->yAxis->setLabel(this->yLabel);
    if(ui->customPlot->plotLayout()->rowCount()==1){
        ui->customPlot->plotLayout()->insertRow(0);
        ui->customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(ui->customPlot, title, QFont("sans", 12, QFont::Bold)));
        ui->customPlot->rescaleAxes(true);//初次绘制要调整下范围
    }
    else{
        QCPTextElement *tit=(QCPTextElement*)ui->customPlot->plotLayout()->element(0,0);
        tit->setText(this->title);
        tit->setFont(QFont("sans", 12, QFont::Bold));
    }
    ui->customPlot->replot();
}

void Plotter2DWidget::printMessage(QString text)
{
    QString message=ui->textEdit->toPlainText();
    message+=("\n  "+text);
    ui->textEdit->setText(message);
    ui->textEdit->moveCursor(QTextCursor::End);
}

void Plotter2DWidget::showContext()
{
    QMenu menu;
    QAction scatterAction("scatter plot");
    QAction continuAction("line plot");
    QAction barAction("histograms");
    QAction zoomAction("rescale axes");
    QAction titleAction("set title");
    QAction xLabelAction("set x label");
    QAction yLabelAction("set y label");
    QAction saveAction("save image");
    QMenu extentedFuncs("more functions");
    QAction elbowAction("elbow search");
    QAction stdElbowAction("elbow search(standardized)");
    scatterAction.setCheckable(true);
    scatterAction.setChecked(this->scatterPlot);
    connect(&scatterAction,&QAction::toggled,[=](bool toggled){
        this->scatterPlot=toggled;
        this->plotData();
        this->printMessage(QString("scatter plot enabled:")+QString(toggled?"true":"false"));
    });
    continuAction.setCheckable(true);
    continuAction.setChecked(this->linePlot);
    connect(&continuAction,&QAction::toggled,[=](bool toggled){
        this->linePlot=toggled;
        this->plotData();
        this->printMessage(QString("line plot enabled:")+QString(toggled?"true":"false"));
    });
    barAction.setCheckable(true);
    barAction.setChecked(this->barPlot);
    connect(&barAction,&QAction::toggled,[=](bool toggled){
        this->barPlot=toggled;
        this->plotData();
        this->printMessage(QString("histogram plot enabled:")+QString(toggled?"true":"false"));
    });
    connect(&zoomAction,&QAction::triggered,[=](){
        this->ui->customPlot->rescaleAxes(true);
        this->ui->customPlot->replot();
    });
    connect(&titleAction,&QAction::triggered,[=](){
        bool ok;
        QString tit=QInputDialog::getText(this,tr("Set title"),tr("please set a new title for the plot (empty string is allowed):"),QLineEdit::Normal,this->title,&ok);
        if(ok&&this->title!=tit){
            this->title=tit;
            this->plotData();
            this->printMessage(QString("set new title:")+this->title);
        }
    });
    connect(&xLabelAction,&QAction::triggered,[=](){
        bool ok;
        QString xText=QInputDialog::getText(this,tr("Set label"),tr("please set a new x label for the plot (empty string is allowed):"),QLineEdit::Normal,this->xLabel,&ok);
        if(ok&&this->xLabel!=xText){
            this->xLabel=xText;
            this->plotData();
            this->printMessage(QString("set new x label:")+this->xLabel);
        }
    });
    connect(&yLabelAction,&QAction::triggered,[=](){
        bool ok;
        QString yText=QInputDialog::getText(this,tr("Set label"),tr("please set a new y label for the plot (empty string is allowed):"),QLineEdit::Normal,this->yLabel,&ok);
        if(ok&&this->yLabel!=yText){
            this->yLabel=yText;
            this->plotData();
            this->printMessage(QString("set new y label:")+this->yLabel);
        }
    });
    connect(&saveAction,&QAction::triggered,[=](){
       QString fileName=QFileDialog::getSaveFileName(this,tr("save image"),tr("."),QString("image file(*.jpg;*.jpeg)"));
       if(fileName!=""){
           ui->customPlot->saveJpg(fileName,ui->customPlot->width(),ui->customPlot->height(),1.0,-1,200);
       }
    });
    connect(&elbowAction,&QAction::triggered,[=](){
        QPointF start,end,maxP,footP;
        this->elbowSearch(start,end,maxP,footP);
        this->showElbowSearch(start,end,maxP,footP);
    });
    connect(&stdElbowAction,&QAction::triggered,[=](){
        QPointF start,end,maxP,footP;
        this->elbowSearch(start,end,maxP,footP,true);
        this->showElbowSearch(start,end,maxP,footP);
    });
    menu.addAction(&scatterAction);
    menu.addAction(&continuAction);
    menu.addAction(&barAction);
    menu.addSeparator();
    menu.addAction(&zoomAction);
    menu.addAction(&titleAction);
    menu.addAction(&xLabelAction);
    menu.addAction(&yLabelAction);
    menu.addAction(&saveAction);
    menu.addSeparator();
    menu.addMenu(&extentedFuncs);
    extentedFuncs.addAction(&elbowAction);
    extentedFuncs.addAction(&stdElbowAction);
    menu.exec(QCursor::pos());
}

void Plotter2DWidget::lineThrough(const QPointF &p1, const QPointF &p2, double &a, double &b, double &c)
{
    //默认两点p1,p2不重合
    if(p1.x()*p2.y()==p1.y()*p2.x()){//直线过原点
        if(p1.x()==p2.y()){//y轴
            a=1;
            b=0;
            c=0;
        }
        else{
            a=(p2.y()-p1.y())/(p2.x()-p1.x());
            b=-1;
            c=0;
        }
    }
    else{
        double D=p1.x()*p2.y()-p1.y()*p2.x();
        double D1=p1.y()-p2.y();
        double D2=p2.x()-p1.x();
        a=D1/D;
        b=D2/D;
        c=-1;
    }
    //归一化
    double norm=sqrt(a*a+b*b);
    a/=norm;
    b/=norm;
    c/=norm;
    //a取正
    if(a<0){
        a=-a;
        b=-b;
        c=-c;
    }
}

void Plotter2DWidget::elbowSearch(QPointF &pStart, QPointF &pEnd, QPointF &pMaxDis, QPointF &foot, bool standardize)
{
    //只适合凸曲线
    double a,b,c;
    QVector<double> xData=this->x;
    QVector<double> yData=this->y;
    double scaleX=1;
    double shiftX=0;
    double scaleY=1;
    double shiftY=0;
    if(standardize){
        std::pair<double*,double*> minMaxX=std::minmax_element(xData.begin(),xData.end());
        std::pair<double*,double*> minMaxY=std::minmax_element(yData.begin(),yData.end());
        scaleX=*minMaxX.second-*minMaxX.first;
        shiftX=*minMaxX.first;
        scaleY=*minMaxY.second-*minMaxY.first;
        shiftY=*minMaxY.first;
        std::for_each(xData.begin(),xData.end(),[=](double &ele){ele=(ele-shiftX)/scaleX;});
        std::for_each(yData.begin(),yData.end(),[=](double &ele){ele=(ele-shiftY)/scaleY;});
    }
    //求首尾线
    QVector<double> line_x(2);
    QVector<double> line_y(2);
    line_x[0]=xData[0];
    line_x[1]=xData[xData.size()-1];
    line_y[0]=yData[0];
    line_y[1]=yData[yData.size()-1];
    this->lineThrough(QPointF(line_x[0],line_y[0]),QPointF(line_x[1],line_y[1]),a,b,c);
    //查找最大偏离首尾连线点
    QVector<int> index(xData.size());
    for(int i=0;i<index.size();++i){
        index[i]=i;
    }
    QVector<int>::iterator iter=std::max_element(index.begin(),index.end(),[=](int idx1,int idx2){
        return abs(a*xData[idx1]+b*yData[idx1]+c)<abs(a*xData[idx2]+b*yData[idx2]+c);
    });
    double x_max=xData[*iter];
    double y_max=yData[*iter];
    //查找垂足
    QPointF vec1(x_max-xData[0],y_max-yData[0]);
    QPointF vec_line(line_x[1]-line_x[0],line_y[1]-line_y[0]);
    auto dotProduct=[](QPointF vec1,QPointF vec2){
        return vec1.x()*vec2.x()+vec1.y()*vec2.y();
    };
    auto vecMod=[](QPointF vec)->double{
        return sqrt(vec.x()*vec.x()+vec.y()*vec.y());
    };
    double mod=vecMod(vec_line);
    QPointF project=dotProduct(vec1,vec_line)/(mod*mod)*vec_line;
    QPointF footPoint=project+QPointF(line_x[0],line_y[0]);
    //赋值
    pStart=QPointF(xData[0]*scaleX+shiftX,yData[0]*scaleY+shiftY);
    pEnd=QPointF(xData[xData.size()-1]*scaleX+shiftX,yData[yData.size()-1]*scaleY+shiftY);
    pMaxDis=QPointF(x_max*scaleX+shiftX,y_max*scaleY+shiftY);
    foot=QPointF(footPoint.x()*scaleX+shiftX,footPoint.y()*scaleY+shiftY);
}

void Plotter2DWidget::showElbowSearch(QPointF &pStart, QPointF &pEnd, QPointF &pMaxDis, QPointF &foot)
{
    QVector<double> line_x(2);
    QVector<double> line_y(2);
    line_x[0]=pStart.x();
    line_x[1]=pEnd.x();
    line_y[0]=pStart.y();
    line_y[1]=pEnd.y();
    ui->customPlot->addGraph();
    int idx=ui->customPlot->graphCount()-1;
    ui->customPlot->graph(idx)->setPen(QColor(255,0,0));
    ui->customPlot->graph(idx)->setData(line_x,line_y);
    this->printMessage(QString("the elbow point is:(%1,%2)").arg(pMaxDis.x()).arg(pMaxDis.y()));
    //绘制垂线
    QVector<double> line_vertx(2);
    QVector<double> line_verty(2);
    line_vertx[0]=pMaxDis.x();
    line_vertx[1]=foot.x();
    line_verty[0]=pMaxDis.y();
    line_verty[1]=foot.y();
    ui->customPlot->addGraph();
    idx=ui->customPlot->graphCount()-1;
    ui->customPlot->graph(idx)->setPen(QColor(255,0,0));
    ui->customPlot->graph(idx)->setData(line_vertx,line_verty);
    ui->customPlot->replot();
}

SignalDelegate::SignalDelegate()
{
    qRegisterMetaType<QVariant>("QVariant");
}

void SignalDelegate::sendSignal(QVector<double> &x, QVector<double> &y)
{
    QVariant xData,yData;
    xData.setValue(x);
    yData.setValue(y);
    emit inputDataChanged(xData,yData);
}
