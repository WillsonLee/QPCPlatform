#include "blobclusterwidget.h"
#include "ui_blobclusterwidget.h"
#include <QStringList>
#include <QDebug>

BlobClusterWidget::BlobClusterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlobClusterWidget)
{
    ui->setupUi(this);
    QStringList list;
    list<<"CV_32S"<<"CV_16U";
    ui->depthComboBox->addItems(list);
    QStringList another;
    another<<"BBDT"<<"SAUF";
    ui->algorithmComboBox->addItems(another);

}

void BlobClusterWidget::initArgs(bool fourNeighbors, int outType, int algorithm,bool removal, int area)
{
    this->fourNeighbors=fourNeighbors;
    this->removal=removal;
    ui->fourRadioButton->setChecked(fourNeighbors);
    ui->eightRadioButton->setChecked(!fourNeighbors);
    ui->depthComboBox->setCurrentIndex(outType);
    ui->algorithmComboBox->setCurrentIndex(algorithm);
    ui->speckleCheckBox->setChecked(removal);
    ui->areaSpinBox->setEnabled(removal);
    ui->areaSpinBox->setValue(area);
}

BlobClusterWidget::~BlobClusterWidget()
{
    delete ui;
}

void BlobClusterWidget::on_fourRadioButton_toggled(bool checked)
{
    if(fourNeighbors!=checked){
        fourNeighbors=checked;
        emit internalArgsChanged(fourNeighbors,ui->depthComboBox->currentIndex(),ui->algorithmComboBox->currentIndex(),removal,ui->areaSpinBox->value());
    }
}

void BlobClusterWidget::on_depthComboBox_currentIndexChanged(int index)
{
    emit internalArgsChanged(fourNeighbors,index,ui->algorithmComboBox->currentIndex(),removal,ui->areaSpinBox->value());
}

void BlobClusterWidget::on_speckleCheckBox_toggled(bool checked)
{
    ui->areaSpinBox->setEnabled(checked);
    if(removal!=checked){
        removal=checked;
        emit internalArgsChanged(fourNeighbors,ui->depthComboBox->currentIndex(),ui->algorithmComboBox->currentIndex(),removal,ui->areaSpinBox->value());
    }
}

void BlobClusterWidget::on_areaSpinBox_valueChanged(int arg1)
{
    emit internalArgsChanged(fourNeighbors,ui->depthComboBox->currentIndex(),ui->algorithmComboBox->currentIndex(),removal,arg1);
}

void BlobClusterWidget::on_algorithmComboBox_currentIndexChanged(int index)
{
    emit internalArgsChanged(fourNeighbors,ui->depthComboBox->currentIndex(),index,removal,ui->areaSpinBox->value());
}
