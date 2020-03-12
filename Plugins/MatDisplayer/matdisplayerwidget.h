#ifndef MATDISPLAYERWIDGET_H
#define MATDISPLAYERWIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>

namespace Ui {
class MatDisplayerWidget;
}

class MatDisplayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatDisplayerWidget(QWidget *parent = 0);
    void setImage(cv::Mat mat);
    ~MatDisplayerWidget();
signals:
//    void internalArgsChanged(int a,int b,int c);
protected:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MatDisplayerWidget *ui;
    QPixmap pix;
};

#endif // MatDisplayerWidget_H
