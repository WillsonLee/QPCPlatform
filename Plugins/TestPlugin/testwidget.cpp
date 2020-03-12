#include "testwidget.h"
#include "ui_testwidget.h"

TestWidget::TestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestWidget)
{
    ui->setupUi(this);
}

void TestWidget::setInitialParas(int a, int b, int c)
{
    ui->aSlider->setValue(a);
    ui->bSlider->setValue(b);
    ui->cSlider->setValue(c);
}

TestWidget::~TestWidget()
{
    delete ui;
}

void TestWidget::on_aSlider_valueChanged(int value)
{
    emit internalArgsChanged(ui->aSlider->value(),ui->bSlider->value(),ui->cSlider->value());
}

void TestWidget::on_bSlider_valueChanged(int value)
{
    emit internalArgsChanged(ui->aSlider->value(),ui->bSlider->value(),ui->cSlider->value());
}

void TestWidget::on_cSlider_valueChanged(int value)
{
    emit internalArgsChanged(ui->aSlider->value(),ui->bSlider->value(),ui->cSlider->value());
}
