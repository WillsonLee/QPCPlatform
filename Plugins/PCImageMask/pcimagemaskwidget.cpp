#include "pcimagemaskwidget.h"
#include "ui_pcimagemaskwidget.h"
#include <QMessageBox>

PCImageMaskWidget::PCImageMaskWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PCImageMaskWidget)
{
    ui->setupUi(this);
}

void PCImageMaskWidget::initArgs(bool autoOffset, bool autoGSD)
{
    ui->offsetCheckBox->setChecked(autoOffset);
    ui->gsdCheckBox->setChecked(autoGSD);
}

void PCImageMaskWidget::setMode(bool binary)
{
    ui->radioButtonBinary->setChecked(binary);
    ui->radioButtonMulti->setChecked(!binary);
}

void PCImageMaskWidget::setInverse(bool inverse)
{
    ui->inverseCheckBox->setChecked(inverse);
}

void PCImageMaskWidget::setAutoParas(double x, double y, double gsd)
{
    if(ui->offsetCheckBox->isChecked()){
        ui->xOffsetEdit->setText(QString::number(x));
        ui->yOffsetEdit->setText(QString::number(y));
    }
    if(ui->gsdCheckBox->isChecked()){
        ui->gsdEdit->setText(QString::number(gsd));
    }
}

PCImageMaskWidget::~PCImageMaskWidget()
{
    delete ui;
}

void PCImageMaskWidget::on_offsetCheckBox_toggled(bool checked)
{
    if(checked){
        ui->xOffsetEdit->setEnabled(false);
        ui->yOffsetEdit->setEnabled(false);
    }
    else{
        ui->xOffsetEdit->setEnabled(true);
        ui->yOffsetEdit->setEnabled(true);
    }
    sendSignal();
}

void PCImageMaskWidget::on_gsdCheckBox_toggled(bool checked)
{
    if(checked){
        ui->gsdEdit->setEnabled(false);
    }
    else{
        ui->gsdEdit->setEnabled(true);
    }
    sendSignal();
}

void PCImageMaskWidget::on_xOffsetEdit_editingFinished()
{
    if(ui->xOffsetEdit->isEnabled()){
        sendSignal();
    }
}

void PCImageMaskWidget::on_yOffsetEdit_editingFinished()
{
    if(ui->yOffsetEdit->isEnabled()){
        sendSignal();
    }
}

void PCImageMaskWidget::on_gsdEdit_editingFinished()
{
    if(ui->gsdEdit->isEnabled()){
        sendSignal();
    }
}

void PCImageMaskWidget::sendSignal()
{
    double x=ui->xOffsetEdit->text().toDouble();
    double y=ui->yOffsetEdit->text().toDouble();
    double gsd=ui->gsdEdit->text().toDouble();
    bool autoOff=ui->offsetCheckBox->isChecked();
    bool autoGSD=ui->gsdCheckBox->isChecked();
    if(gsd<=0){
        ui->gsdEdit->setFocus();
    }
    else{
        emit argsChanged(x,y,gsd,autoOff,autoGSD);
    }
}

void PCImageMaskWidget::on_radioButtonMulti_toggled(bool checked)
{
    emit modeChanged(!checked);
}

void PCImageMaskWidget::on_inverseCheckBox_toggled(bool checked)
{
    ui->maskTypeGroup->setEnabled(!checked);
    if(checked){
        emit inverseStateChanged(checked);
    }
}
