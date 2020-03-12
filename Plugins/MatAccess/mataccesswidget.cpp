#include "mataccesswidget.h"
#include "ui_mataccesswidget.h"

MatAccessWidget::MatAccessWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatAccessWidget)
{
    ui->setupUi(this);
    ui->rowSpin->setValue(0);
    ui->colSpin->setValue(0);
    ui->channelSpin->setValue(0);
}

void MatAccessWidget::setMaximum(int ax, int bx, int cx)
{
    if(ax!=ui->rowSpin->maximum()){
        ui->rowSpin->setMaximum(ax);
        ui->rowLabel->setText(QString("Row(%1):").arg(ax+1));
    }
    if(bx!=ui->colSpin->maximum()){
        ui->colSpin->setMaximum(bx);
        ui->colLabel->setText(QString("Col(%1):").arg(bx+1));
    }
    if(cx!=ui->channelSpin->maximum()){
        ui->channelSpin->setMaximum(cx);
        ui->chaLabel->setText(QString("Channel(%1):").arg(cx+1));
    }
    bool changed=false;
    if(ui->rowSpin->value()>ax){
        ui->rowSpin->setValue(0);
        changed=true;
    }
    if(ui->colSpin->value()>bx){
        ui->colSpin->setValue(0);
        changed=true;
    }
    if(ui->channelSpin->value()>cx){
        ui->channelSpin->setValue(0);
        changed=true;
    }
    if(changed){
        emit this->internalArgsChanged(ui->rowSpin->value(),ui->colSpin->value(),ui->channelSpin->value());
    }
}

void MatAccessWidget::setDepthLabel(QString text)
{
    ui->depthLabel->setText(text);
}

MatAccessWidget::~MatAccessWidget()
{
    delete ui;
}

void MatAccessWidget::on_rowSpin_valueChanged(int arg1)
{
    emit this->internalArgsChanged(ui->rowSpin->value(),ui->colSpin->value(),ui->channelSpin->value());
}

void MatAccessWidget::on_colSpin_valueChanged(int arg1)
{
    emit this->internalArgsChanged(ui->rowSpin->value(),ui->colSpin->value(),ui->channelSpin->value());
}

void MatAccessWidget::on_channelSpin_valueChanged(int arg1)
{
    emit this->internalArgsChanged(ui->rowSpin->value(),ui->colSpin->value(),ui->channelSpin->value());
}
