#include "matdisplayerwidget.h"
#include "ui_matdisplayerwidget.h"
#include <QImage>
#include <QVector>
#include <QRgb>
#include <QDebug>

MatDisplayerWidget::MatDisplayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatDisplayerWidget)
{
    ui->setupUi(this);
}

void MatDisplayerWidget::setImage(cv::Mat mat)
{
    QImage qImg;
    if(mat.type()!=CV_8UC(mat.channels())){
        mat.convertTo(mat,CV_8UC(mat.channels()));
    }
    if(mat.type()==CV_8UC4){
        qImg=QImage(mat.data,mat.cols,mat.rows,mat.step,QImage::Format_RGB32);
        qImg=qImg.rgbSwapped();
    }
    else if(mat.type()==CV_8UC3){
        qImg=QImage(mat.data,mat.cols,mat.rows,mat.step,QImage::Format_RGB888);
        qImg=qImg.rgbSwapped();
    }
    else if(mat.type()==CV_8UC1){
        static QVector<QRgb> sColorTable;
        if(sColorTable.isEmpty()){
            for(int i=0;i<256;++i){
                sColorTable.push_back(qRgb(i,i,i));
            }
        }
        qImg=QImage(mat.data,mat.cols,mat.rows,mat.step,QImage::Format_Indexed8);
        qImg.setColorTable(sColorTable);
    }
    else{
        throw std::exception("image with two channels is unable to display,please convert it to single channel or three or four channel image!");
    }
    pix=QPixmap::fromImage(qImg);
    ui->imageLabel->setAlignment(Qt::AlignCenter);
    ui->imageLabel->setPixmap(pix.scaled(ui->imageLabel->size(),Qt::KeepAspectRatio));
    ui->imageLabel->update();
}

MatDisplayerWidget::~MatDisplayerWidget()
{
    delete ui;
}

void MatDisplayerWidget::resizeEvent(QResizeEvent *event)
{
    ui->imageLabel->setPixmap(pix.scaled(ui->imageLabel->size(),Qt::KeepAspectRatio));
    ui->imageLabel->update();
}
