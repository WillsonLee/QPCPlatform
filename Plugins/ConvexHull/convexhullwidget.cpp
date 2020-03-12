#include "convexhullwidget.h"
#include "ui_convexhullwidget.h"
#include <QStringList>

ConvexHullWidget::ConvexHullWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConvexHullWidget)
{
    ui->setupUi(this);
    QStringList items;
    items<<"javis"<<"graham";
    ui->comboBox->addItems(items);
    ui->comboBox->setCurrentIndex(0);
}

void ConvexHullWidget::initArgs(bool binary, int algo)
{
    ui->binaryRadio->setChecked(binary);
    ui->multiRadio->setChecked(!binary);
    ui->comboBox->setCurrentIndex(algo);
}

ConvexHullWidget::~ConvexHullWidget()
{
    delete ui;
}

void ConvexHullWidget::on_binaryRadio_toggled(bool checked)
{
    emit argsChanged(checked,ui->comboBox->currentIndex());
}

void ConvexHullWidget::on_comboBox_currentIndexChanged(int index)
{
    emit argsChanged(ui->binaryRadio->isChecked(),index);
}
