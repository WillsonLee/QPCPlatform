#include "pcdloaderwidget.h"
#include "ui_pcdloaderwidget.h"
#include <QFileDialog>

PCDLoaderWidget::PCDLoaderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PCDLoaderWidget)
{
    ui->setupUi(this);
    QStringList list;
    list<<"PointXYZ"<<"PointXYZRGB";
    ui->comboBox->addItems(list);
}

void PCDLoaderWidget::initParameters(QString name, int type)
{
    ui->lineEdit->setText(name);
    ui->comboBox->setCurrentIndex(type);
}

PCDLoaderWidget::~PCDLoaderWidget()
{
    delete ui;
}

void PCDLoaderWidget::on_pushButton_clicked()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("open file"),"",tr("PCD Files(*.pcd)"));
    ui->lineEdit->setText(fileName);
    if(fileName!="")emit internalArgsChanged(fileName,ui->comboBox->currentIndex());
}

void PCDLoaderWidget::on_comboBox_currentIndexChanged(int index)
{
    emit internalArgsChanged(ui->lineEdit->text(),index);
}
