#ifndef PLOTTER2DWIDGET_H
#define PLOTTER2DWIDGET_H

#include <QWidget>
#include <QVector>
#include <qcustomplot.h>
#include <QMetaType>
#include <QVariant>
Q_DECLARE_METATYPE(QVector<double>)

class SignalDelegate:public QObject
{
    Q_OBJECT

public:
    SignalDelegate();
    void sendSignal(QVector<double> &x, QVector<double> &y);
signals:
    void inputDataChanged(QVariant x,QVariant y);
};

namespace Ui {
class Plotter2DWidget;
}

class Plotter2DWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Plotter2DWidget(QWidget *parent = 0);
    ~Plotter2DWidget();
private:
    Ui::Plotter2DWidget *ui;
    int marker_size;
    QVector<double> x;
    QVector<double> y;
    QString xLabel;
    QString yLabel;
    QString title;
    bool scatterPlot;
    bool linePlot;
    bool barPlot;
    bool enableInteraction;
    void setData(QVector<double> &x,QVector<double> &y);
    void plotData();
    void printMessage(QString text);
    void lineThrough(const QPointF &p1,const QPointF &p2,double &a,double &b,double &c);
    void elbowSearch(QPointF &pStart,QPointF &pEnd,QPointF &pMaxDis,QPointF &foot,bool standardize=false);
    void showElbowSearch(QPointF &pStart,QPointF &pEnd,QPointF &pMaxDis,QPointF &foot);
public slots:
    void onDataChange(QVariant x,QVariant y);
    void showContext();
};

#endif // Plotter2DWidget_H
