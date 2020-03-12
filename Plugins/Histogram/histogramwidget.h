#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include <QWidget>

namespace Ui {
class HistogramWidget;
}

class HistogramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistogramWidget(QWidget *parent = 0);
    void initArgs(int channels,bool norm,bool accumulate,int bins1,float min1,float max1,int bins2,float min2,float max2);
    void setBinsEdge(int edge);
    void setTotalChannels(int num);
    void setAutoMinMax(bool auto1,bool auto2);
    ~HistogramWidget();
signals:
    void internalArgsChanged(int channels,bool norm,bool accumulate,int bins1,float min1,float max1,int bins2,float min2,float max2);
    void channelsChanged(int channel1,int channel2);
    void binsEdgeChanged(int edge);//edge=0:left;1:middle;2:right
    void binsRangeAutoChanged(bool isAuto1,bool isAuto2);

private slots:
    void on_spinBoxChannels_valueChanged(int arg1);

    void on_checkBoxNorm_toggled(bool checked);

    void on_checkBoxAccumu_toggled(bool checked);

    void on_spinBoxBins1_valueChanged(int arg1);

    void on_lineEditMin1_editingFinished();

    void on_lineEditMax1_editingFinished();

    void on_spinBoxBins2_valueChanged(int arg1);

    void on_lineEditMin2_editingFinished();

    void on_lineEditMax2_editingFinished();

    void on_comboBoxChannel1_currentIndexChanged(int index);

    void on_comboBoxChannel2_currentIndexChanged(int index);

    void binsEdgeSelect();

    void on_checkBoxAuto1_toggled(bool checked);

    void on_checkBoxAuto2_toggled(bool checked);

private:
    Ui::HistogramWidget *ui;
    void sendSignal();
};

#endif // HistogramWidget_H
