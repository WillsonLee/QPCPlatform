#include "minboundingboxwidget.h"
#include "ui_minboundingboxwidget.h"

MinBoundingBoxWidget::MinBoundingBoxWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MinBoundingBoxWidget)
{
    ui->setupUi(this);
}

void MinBoundingBoxWidget::initArgs(bool binary, bool merge, int node)
{
    ui->radioButtonBinary->setChecked(binary);
    ui->radioButtonMulti->setChecked(!binary);
    ui->checkBoxMerge->setChecked(merge);
    if(0<node&&node<=4){
        ui->nodeSpinBox->setValue(node);
    }
}

MinBoundingBoxWidget::~MinBoundingBoxWidget()
{
    delete ui;
}

void MinBoundingBoxWidget::on_radioButtonBinary_toggled(bool checked)
{
    ui->checkBoxMerge->setEnabled(ui->radioButtonMulti->isChecked());
    emit internalArgsChanged(checked,ui->checkBoxMerge->isChecked(),ui->nodeSpinBox->value());
}

void MinBoundingBoxWidget::on_checkBoxMerge_toggled(bool checked)
{
    emit internalArgsChanged(ui->radioButtonBinary->isChecked(),checked,ui->nodeSpinBox->value());
}

void MinBoundingBoxWidget::on_nodeSpinBox_valueChanged(int arg1)
{
    emit internalArgsChanged(ui->radioButtonBinary->isChecked(),ui->checkBoxMerge->isChecked(),arg1);
}
