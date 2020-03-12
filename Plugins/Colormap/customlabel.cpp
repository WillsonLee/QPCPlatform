#include "customlabel.h"
#include <QPainter>

CustomLabel::CustomLabel(QWidget *parent):QLabel(parent)
{
    grad=QLinearGradient(QPointF(0,0),QPointF(this->width(),0));
}

void CustomLabel::setColors(QColor c1,QColor c2)
{
    this->c1=c1;
    this->c2=c2;
}

void CustomLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    grad=QLinearGradient(QPointF(0,0),QPointF(this->width(),0));
    grad.setColorAt(0,c1);
    grad.setColorAt(1,c2);
    grad.setSpread(QGradient::PadSpread);
    painter.setBrush(grad);
    painter.drawRect(QRect(0,0,this->contentsRect().width(),this->contentsRect().height()));
}
