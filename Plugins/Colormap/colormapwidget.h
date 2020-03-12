#ifndef COLORMAPWIDGET_H
#define COLORMAPWIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include <QVector>
#include <QColor>

namespace Ui {
class ColormapWidget;
}

class ColormapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColormapWidget(QWidget *parent = 0);
    void initArgs(bool randomColor,int bins,bool maxBins);
    ~ColormapWidget();
signals:
    void internalArgsChanged(bool randomColor,int bins,bool maxBins,cv::Scalar min_color,cv::Scalar max_color);

private slots:
    void on_rdBttnRandom_toggled(bool checked);

    void on_spnBxBins_valueChanged(int arg1);

    void on_chckBxAuto_toggled(bool checked);

    void on_cmbBxColormap_currentIndexChanged(int index);

    void on_pshBttnMinColor_clicked();

    void on_pshBttnMaxColor_clicked();

private:
    Ui::ColormapWidget *ui;
    cv::Scalar min_color;
    cv::Scalar max_color;
    QVector<QColor> minSelection;
    QVector<QColor> maxSelection;
private:
    void setMinMaxColor(cv::Scalar min,cv::Scalar max);
};

#endif // ColormapWidget_H
