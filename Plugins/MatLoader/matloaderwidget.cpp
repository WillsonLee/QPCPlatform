#include "matloaderwidget.h"
#include "ui_matloaderwidget.h"
#include <opencv2/opencv.hpp>
#include <QFileDialog>
#include <QDebug>

MatLoaderWidget::MatLoaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatLoaderWidget)
{
    ui->setupUi(this);
}

void MatLoaderWidget::initParas(std::string fileName, int mode)
{
    ui->fileLineEdit->setText(QString::fromStdString(fileName));
    QStringList list;
    list<<"IMREAD_UNCHANGED"<<"IMREAD_GRAYSCALE"<<"IMREAD_COLOR"<<"IMREAD_ANYDEPTH"<<"IMREAD_LOAD_GDAL"<<"IMREAD_REDUCED_GRAYSCALE_2"<<"IMREAD_REDUCED_COLOR_2"
       <<"IMREAD_REDUCED_GRAYSCALE_4"<<"IMREAD_REDUCED_COLOR_4"<<"IMREAD_REDUCED_GRAYSCALE_8"<<"IMREAD_REDUCED_COLOR_8"<<"IMREAD_IGNORE_ORIENTATION";
    mapIndexToMode.clear();
    mapIndexToMode[0]=-1;//   IMREAD_UNCHANGED            = -1, //!< If set, return the loaded image as is (with alpha channel, otherwise it gets cropped).
    mapIndexToMode[1]=0;//    IMREAD_GRAYSCALE            = 0,  //!< If set, always convert image to the single channel grayscale image (codec internal conversion).
    mapIndexToMode[2]=1;//    IMREAD_COLOR                = 1,  //!< If set, always convert image to the 3 channel BGR color image.
    mapIndexToMode[3]=2;//    IMREAD_ANYDEPTH             = 2,  //!< If set, return 16-bit/32-bit image when the input has the corresponding depth, otherwise convert it to 8-bit.
    mapIndexToMode[4]=4;//    IMREAD_ANYCOLOR             = 4,  //!< If set, the image is read in any possible color format.
    mapIndexToMode[5]=8;//    IMREAD_LOAD_GDAL            = 8,  //!< If set, use the gdal driver for loading the image.
    mapIndexToMode[6]=16;//   IMREAD_REDUCED_GRAYSCALE_2  = 16, //!< If set, always convert image to the single channel grayscale image and the image size reduced 1/2.
    mapIndexToMode[7]=17;//   IMREAD_REDUCED_COLOR_2      = 17, //!< If set, always convert image to the 3 channel BGR color image and the image size reduced 1/2.
    mapIndexToMode[8]=32;//   IMREAD_REDUCED_GRAYSCALE_4  = 32, //!< If set, always convert image to the single channel grayscale image and the image size reduced 1/4.
    mapIndexToMode[9]=33;//   IMREAD_REDUCED_COLOR_4      = 33, //!< If set, always convert image to the 3 channel BGR color image and the image size reduced 1/4.
    mapIndexToMode[10]=64;//  IMREAD_REDUCED_GRAYSCALE_8  = 64, //!< If set, always convert image to the single channel grayscale image and the image size reduced 1/8.
    mapIndexToMode[11]=65;//  IMREAD_REDUCED_COLOR_8      = 65, //!< If set, always convert image to the 3 channel BGR color image and the image size reduced 1/8.
    mapIndexToMode[12]=128;// IMREAD_IGNORE_ORIENTATION   = 128 //!< If set, do not rotate the image according to EXIF's orientation flag.
    mapModeToIndex.clear();
    for(int i=0;i<13;++i){
        mapModeToIndex[mapIndexToMode[i]]=i;
    }
    ui->modeComboBox->addItems(list);
    ui->modeComboBox->setCurrentIndex(mapModeToIndex[mode]);
}

MatLoaderWidget::~MatLoaderWidget()
{
    delete ui;
}

void MatLoaderWidget::on_openPushButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("open image file"),tr("D:"),tr("image file(*.png *.jpg *.jpeg *.tiff *.tif)"));
    if(fileName!=""&&fileName!=ui->fileLineEdit->text()){
        ui->fileLineEdit->setText(fileName);
        emit internalArgsChanged(fileName.toStdString(),this->mapIndexToMode[ui->modeComboBox->currentIndex()]);
    }
}

void MatLoaderWidget::on_modeComboBox_currentIndexChanged(int index)
{
    emit internalArgsChanged(ui->fileLineEdit->text().toStdString(),this->mapIndexToMode[ui->modeComboBox->currentIndex()]);
}
