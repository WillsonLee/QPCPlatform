#include "gammatransformwidget.h"
#include "ui_gammatransformwidget.h"

GammaTransformWidget::GammaTransformWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GammaTransformWidget)
{
    ui->setupUi(this);
}

void GammaTransformWidget::initArgs(double gamma)
{
    this->gamma=gamma;
    ui->doubleSpinBox->setValue(gamma);
}

GammaTransformWidget::~GammaTransformWidget()
{
    delete ui;
}

void GammaTransformWidget::on_doubleSpinBox_valueChanged(double arg1)
{
    if(arg1!=gamma){
        gamma=arg1;
        emit internalArgsChanged(arg1);
    }
    if(arg1<=0.1){
        ui->doubleSpinBox->setSingleStep(0.01);
    }
    else if(arg1<=1){
        ui->doubleSpinBox->setSingleStep(0.1);
    }
    else if(arg1<=10){
        ui->doubleSpinBox->setSingleStep(1);
    }
    else{
        ui->doubleSpinBox->setSingleStep(10);
    }
}
