#ifndef HOUGHLINESWIDGET_H
#define HOUGHLINESWIDGET_H

#include <QWidget>

namespace Ui {
class HoughLinesWidget;
}

class HoughLinesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HoughLinesWidget(QWidget *parent = 0);
    void initArgs(double rho,double theta,int thresh,double minLength,double maxGap);
    ~HoughLinesWidget();
signals:
    void argsChanged(double rho,double theta,int thresh,double minLength,double maxGap);

private slots:
    void on_rhoDoubleSpin_editingFinished();

    void on_thetaDoubleSpin_editingFinished();

    void on_threshSpin_editingFinished();

    void on_minLengthSlider_sliderMoved(int position);

    void on_maxGapSlider_sliderMoved(int position);

    void on_minLengthSlider_sliderReleased();

    void on_maxGapSlider_sliderReleased();

private:
    Ui::HoughLinesWidget *ui;
};

#endif // HoughLinesWidget_H
