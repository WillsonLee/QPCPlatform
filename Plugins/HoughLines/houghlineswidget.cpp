#include "houghlineswidget.h"
#include "ui_houghlineswidget.h"
#include <QToolTip>

HoughLinesWidget::HoughLinesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HoughLinesWidget)
{
    ui->setupUi(this);
}

void HoughLinesWidget::initArgs(double rho, double theta, int thresh, double minLength, double maxGap)
{
    ui->rhoDoubleSpin->setValue(rho);
    ui->thetaDoubleSpin->setValue(theta);
    ui->threshSpin->setValue(thresh);
    ui->minLengthSlider->setValue(minLength);
    ui->maxGapSlider->setValue(maxGap);
}

HoughLinesWidget::~HoughLinesWidget()
{
    delete ui;
}

void HoughLinesWidget::on_rhoDoubleSpin_editingFinished()
{
    emit argsChanged(ui->rhoDoubleSpin->value(),ui->thetaDoubleSpin->value(),ui->threshSpin->value(),ui->minLengthSlider->value(),ui->maxGapSlider->value());
}

void HoughLinesWidget::on_thetaDoubleSpin_editingFinished()
{
    emit argsChanged(ui->rhoDoubleSpin->value(),ui->thetaDoubleSpin->value(),ui->threshSpin->value(),ui->minLengthSlider->value(),ui->maxGapSlider->value());
}

void HoughLinesWidget::on_threshSpin_editingFinished()
{
    emit argsChanged(ui->rhoDoubleSpin->value(),ui->thetaDoubleSpin->value(),ui->threshSpin->value(),ui->minLengthSlider->value(),ui->maxGapSlider->value());
}

void HoughLinesWidget::on_minLengthSlider_sliderMoved(int position)
{
   QToolTip::showText(QCursor::pos(),QString::number(position),ui->minLengthSlider);
}

void HoughLinesWidget::on_maxGapSlider_sliderMoved(int position)
{
    QToolTip::showText(QCursor::pos(),QString::number(position),ui->maxGapSlider);
}

void HoughLinesWidget::on_minLengthSlider_sliderReleased()
{
    emit argsChanged(ui->rhoDoubleSpin->value(),ui->thetaDoubleSpin->value(),ui->threshSpin->value(),ui->minLengthSlider->value(),ui->maxGapSlider->value());
}

void HoughLinesWidget::on_maxGapSlider_sliderReleased()
{
    emit argsChanged(ui->rhoDoubleSpin->value(),ui->thetaDoubleSpin->value(),ui->threshSpin->value(),ui->minLengthSlider->value(),ui->maxGapSlider->value());
}
