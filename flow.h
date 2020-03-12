#ifndef FLOW_H
#define FLOW_H

#include <QWidget>
#include <QPointF>
#include <QPainterPath>
#include <QVector>
#include <Any.h>
#include <QColor>
#include <QTimer>

namespace Ui {
class Flow;
}
/**
 * @brief The Flow class 数据流类,管理数据的流动与流动效果显示,充当上游插件输出与下游插件输入之间的媒介,当上游插件输出更新,提醒与之相连的下游插件的输入更新
 */
class Flow : public QWidget
{
    Q_OBJECT

public:
    explicit Flow(QWidget *parent = 0);
    ~Flow();

    void setStartNode(const QPointF &p);
    void setEndNode(const QPointF &p);
    std::string peekType();
    bool dataIsNull();
    Any getData();
    void setData(const Any &value);
    void setLineColor(QColor c);
    void freezeFlow(bool notFlowing);
signals:
    void dataChanged(Flow *obj);//表示obj中的data变了的信号
    void mouseMoved(QPointF mousePosGlobal);
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::Flow *ui;
    QPointF startNode;
    QPointF endNode;
    QPainterPath path;
    QString dataType;
    Any data;
    QColor lineColor;
    int lineWidth;
    //曲线参数
    QPointF p1;
    QPointF p4;
    qreal c1x,c2x,c1y,c2y;
    bool flowing;
    float t;
    float flowSpeed;
    QPointF flowCircle;
    QTimer *timer;
private:
    void generatePath();
    void updateFlow();
};

#endif // FLOW_H
