#include "flow.h"
#include "ui_flow.h"
#include <QPainter>
#include <cmath>
#include <QDebug>
#include <QMouseEvent>

Flow::Flow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Flow)
{
    ui->setupUi(this);
    this->startNode=QPointF(0,0);
    this->endNode=QPointF(0,0);
    lineColor=Qt::blue;
    lineWidth=3;
    flowing=false;
    timer=new QTimer();
    t=0;
    flowSpeed=0.04;
    connect(timer,&QTimer::timeout,this,&Flow::updateFlow);
    //设置鼠标跟踪
    this->setMouseTracking(true);
}

Flow::~Flow()
{
    delete ui;
    delete timer;
}

void Flow::setStartNode(const QPointF &p)
{
    this->startNode=p;
    generatePath();
    this->update();
}

void Flow::setEndNode(const QPointF &p)
{
    this->endNode=QPointF(p.x(),p.y());
    this->generatePath();
    this->update();
}

std::string Flow::peekType()
{
    return data.getType();
}

bool Flow::dataIsNull()
{
    return data.isNull();
}

void Flow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(QPen(lineColor,lineWidth,Qt::SolidLine,Qt::FlatCap,Qt::RoundJoin));
    painter.drawPath(this->path);
    if(this->flowing){
        painter.setBrush(lineColor);
        painter.drawEllipse(flowCircle,lineWidth,lineWidth);
    }
}

void Flow::mouseMoveEvent(QMouseEvent *event)
{
    emit mouseMoved(event->globalPos());
}

void Flow::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();
}

void Flow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Delete){
        delete this;
    }
}

Any Flow::getData()
{
    this->freezeFlow(true);
    return data;
}

void Flow::setData(const Any &value)
{
    data.setData(value);
    this->freezeFlow(false);
    emit dataChanged(this);
}

void Flow::generatePath()
{
    if(this->startNode.isNull())return;
    path=QPainterPath();
    float min_diff_x=100;
    float diff_x=this->endNode.x()-this->startNode.x();
    float max_x,min_x,shift_x;
    float c1x_p,c2x_p;
    if(diff_x>=0){
        shift_x=diff_x>2*min_diff_x?diff_x/2:min_diff_x;
        c1x_p=this->startNode.x()+shift_x;
        max_x=this->endNode.x()>c1x_p?this->endNode.x():c1x_p;
        min_x=this->startNode.x()+this->endNode.x()-max_x;
        c2x_p=this->endNode.x()-shift_x;
    }
    else{
        shift_x=-diff_x>min_diff_x?-diff_x:min_diff_x;
        min_x=this->endNode.x()-shift_x;
        max_x=this->startNode.x()+this->endNode.x()-min_x;
        c1x_p=max_x;
        c2x_p=min_x;
    }
    float min_y=this->startNode.y()<this->endNode.y()?this->startNode.y():this->endNode.y();
    float max_y=this->startNode.y()>this->endNode.y()?this->startNode.y():this->endNode.y();
    this->setGeometry(QRect(QPoint(min_x,min_y),QPoint(max_x,max_y)));
    p1=this->startNode-this->geometry().topLeft();
    p4=this->endNode-this->geometry().topLeft();
    path.moveTo(p1);
    if(this->endNode.isNull()||p1==p4)
        return;
    c1x=c1x_p-this->geometry().left();
    c1y=p1.y();
    c2x=c2x_p-this->geometry().left();
    c2y=p4.y();
    path.cubicTo(c1x,c1y,c2x,c2y,p4.x(),p4.y());
}

void Flow::updateFlow()
{
    t+=flowSpeed;
    t-=(int)t;
    QPointF p2(c1x,c1y);
    QPointF p3(c2x,c2y);
    flowCircle=pow(1-t,3)*p1+3*pow(1-t,2)*t*p2+3*pow(t,2)*(1-t)*p3+pow(t,3)*p4;
    this->update();
}

void Flow::freezeFlow(bool notFlowing)
{
    this->flowing=(!notFlowing);
    if(!notFlowing){//设置流动特效
        timer->start(40);
    }
    else{
        t=0;
        timer->stop();
    }
}

void Flow::setLineColor(QColor c)
{
    this->lineColor=c;
    this->update();
}
