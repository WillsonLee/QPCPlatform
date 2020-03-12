#ifndef MORPHOLOGYWIDGET_H
#define MORPHOLOGYWIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>

namespace Ui {
class MorphologyWidget;
}

class MorphologyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MorphologyWidget(QWidget *parent = 0);
    void initArgs(int morphType,int shape,int width,int height,int anchorX,int anchorY,int iter,int borderType,cv::Scalar borderValue);
    ~MorphologyWidget();
signals:
    void argsChanged(int morphType,int shape,int width,int height,int anchorX,int anchorY,int iter,int borderType,cv::Scalar borderValue);

private slots:
    void on_morphTypeCombo_currentIndexChanged(int index);

    void on_shapeComboBox_currentIndexChanged(int index);

    void on_widthSpin_valueChanged(int arg1);

    void on_heightSpin_valueChanged(int arg1);

    void on_anchorXSpin_valueChanged(int arg1);

    void on_anchorYSpin_valueChanged(int arg1);

    void on_iterSpin_valueChanged(int arg1);

    void on_borderTypeCombo_currentIndexChanged(int index);

    void on_borderValueEdit_editingFinished();

private:
    Ui::MorphologyWidget *ui;
private:
    void emitSignal();
};

#endif // MorphologyWidget_H
