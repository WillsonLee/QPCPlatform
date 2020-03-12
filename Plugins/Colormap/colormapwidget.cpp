#include "colormapwidget.h"
#include "ui_colormapwidget.h"
#include <QPalette>
#include <QLinearGradient>
#include <QLatin1Char>
#include <QColorDialog>
#include <QDebug>

ColormapWidget::ColormapWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColormapWidget)
{
    ui->setupUi(this);
    //Greys
    minSelection.push_back(QColor(Qt::white));
    maxSelection.push_back(QColor(Qt::black));
    //Blues
    minSelection.push_back(QColor(Qt::white));
    maxSelection.push_back(QColor(Qt::blue));
    //Greens
    minSelection.push_back(QColor(Qt::white));
    maxSelection.push_back(QColor(Qt::green));
    //Reds
    minSelection.push_back(QColor(Qt::white));
    maxSelection.push_back(QColor(Qt::red));
    //Cyans
    minSelection.push_back(QColor(Qt::white));
    maxSelection.push_back(QColor(Qt::cyan));
    //Magentas
    minSelection.push_back(QColor(Qt::white));
    maxSelection.push_back(QColor(Qt::magenta));
    //Yellows
    minSelection.push_back(QColor(Qt::white));
    maxSelection.push_back(QColor(Qt::yellow));
    //RedBlue
    minSelection.push_back(QColor(Qt::red));
    maxSelection.push_back(QColor(Qt::blue));
    //RedGreen
    minSelection.push_back(QColor(Qt::red));
    maxSelection.push_back(QColor(Qt::green));
    QStringList list;
    list<<"Greys"<<"Blues"<<"Greens"<<"Reds"<<"Cyans"<<"Magentas"<<"Yellows"<<"RedBlue"<<"RedGreen";
    ui->cmbBxColormap->addItems(list);
}

void ColormapWidget::initArgs(bool randomColor, int bins, bool maxBins)
{
    ui->rdBttnRandom->setChecked(randomColor);
    ui->rdBttnScale->setChecked(!randomColor);
    ui->spnBxBins->setValue(bins);
    ui->chckBxAuto->setChecked(maxBins);
    ui->cmbBxColormap->setCurrentIndex(0);
}

ColormapWidget::~ColormapWidget()
{
    delete ui;
}

void ColormapWidget::on_rdBttnRandom_toggled(bool checked)
{
    ui->groupBoxScale->setEnabled(!checked);
    emit internalArgsChanged(checked,ui->spnBxBins->value(),ui->chckBxAuto->isChecked(),min_color,max_color);
}

void ColormapWidget::on_spnBxBins_valueChanged(int arg1)
{
    emit internalArgsChanged(ui->rdBttnRandom->isChecked(),arg1,ui->chckBxAuto->isChecked(),min_color,max_color);
}

void ColormapWidget::on_chckBxAuto_toggled(bool checked)
{
    ui->spnBxBins->setEnabled(!checked);
    emit internalArgsChanged(ui->rdBttnRandom->isChecked(),ui->spnBxBins->value(),checked,min_color,max_color);
}

void ColormapWidget::on_cmbBxColormap_currentIndexChanged(int index)
{
    QColor min=minSelection[index];
    QColor max=maxSelection[index];
    setMinMaxColor(cv::Scalar(min.red(),min.green(),min.blue()),cv::Scalar(max.red(),max.green(),max.blue()));
}

void ColormapWidget::on_pshBttnMinColor_clicked()
{
    QColor min=QColorDialog::getColor(QColor(min_color[0],min_color[1],min_color[2]),this,tr("color dialog"));
    cv::Scalar minS=cv::Scalar(min.red(),min.green(),min.blue());
    setMinMaxColor(minS,max_color);
}

void ColormapWidget::on_pshBttnMaxColor_clicked()
{
    QColor max=QColorDialog::getColor(QColor(min_color[0],min_color[1],min_color[2]),this,tr("color dialog"));
    cv::Scalar maxS=cv::Scalar(max.red(),max.green(),max.blue());
    setMinMaxColor(min_color,maxS);
}

void ColormapWidget::setMinMaxColor(cv::Scalar min, cv::Scalar max)
{
    bool sigInNeed=false;
    if(min_color!=min||max_color!=max){
        sigInNeed=true;
    }
    min_color=min;
    max_color=max;
    if(sigInNeed){
        //垃圾QT设置个按钮颜色还要使用stylesheet,你妈炸了,还要把QColor转成字符串
        //好比两个都会说中文的人交流还要拉上一个中文西班牙语翻译把中文翻译成西班牙语再让一个西班牙语中文翻译将它翻译回来
        //QT真是聪明绝顶
        int minRGB=(int(min[0])<<16)+(int(min[1])<<8)+(int(min[2]));
        QString minStr=QString("%1").arg(minRGB,6,16,QLatin1Char('0'));
        ui->pshBttnMinColor->setStyleSheet("background:#"+minStr);
        int maxRGB=(int(max[0])<<16)+(int(max[1])<<8)+(int(max[2]));
        QString maxStr=QString("%1").arg(maxRGB,6,16,QLatin1Char('0'));
        ui->pshBttnMaxColor->setStyleSheet("background:#"+maxStr);
        //要使标签渐变填充,这么一点点小事几个小时都弄不好,QT十分高效
        QColor minC(min[0],min[1],min[2]);
        QColor maxC(max[0],max[1],max[2]);
        ui->lblPreview->setColors(minC,maxC);
        ui->lblPreview->update();
        emit internalArgsChanged(ui->rdBttnRandom->isChecked(),ui->spnBxBins->value(),ui->chckBxAuto->isChecked(),min_color,max_color);
    }
}
