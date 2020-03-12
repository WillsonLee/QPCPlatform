#include "morphologywidget.h"
#include "ui_morphologywidget.h"
#include <QStringList>
#include <QRegExp>
#include <QRegExpValidator>

MorphologyWidget::MorphologyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MorphologyWidget)
{
    ui->setupUi(this);
    QStringList list;
    list<<"ERODE"<<"DILATE"<<"OPEN"<<"CLOSE"<<"GRADIENT"<<"TOPHAT"<<"BLACKHAT"<<"HITMISS";
    ui->morphTypeCombo->addItems(list);
    QStringList shapes;
    shapes<<"RECT"<<"CROSS"<<"ELLIPSE";
    ui->shapeComboBox->addItems(shapes);
    QStringList borders;
    borders<<"CONSTANT"<<"REPLICATE"<<"REFLECT"<<"WRAP"<<"REFLECT_101"<<"TRANSPARENT"<<"ISOLATED";
    ui->borderTypeCombo->addItems(borders);
    ui->borderValueEdit->setValidator(new QRegExpValidator(QRegExp("[-0-9\.,]+")));
}

void MorphologyWidget::initArgs(int morphType, int shape, int width, int height, int anchorX, int anchorY, int iter, int borderType, cv::Scalar borderValue)
{
    ui->morphTypeCombo->setCurrentIndex(morphType);
    ui->shapeComboBox->setCurrentIndex(shape);
    ui->widthSpin->setValue(width);
    ui->heightSpin->setValue(height);
    ui->anchorXSpin->setValue(anchorX);
    ui->anchorYSpin->setValue(anchorY);
    ui->iterSpin->setValue(iter);
    ui->borderTypeCombo->setCurrentIndex(borderType);
    QString values="";
    for(int i=0;i<4;++i){
        if(i)values+=",";
        values+=QString::number(borderValue[i]);
    }
    ui->borderValueEdit->setText(values);
}

MorphologyWidget::~MorphologyWidget()
{
    delete ui;
}

void MorphologyWidget::on_morphTypeCombo_currentIndexChanged(int index)
{
    emitSignal();
}

void MorphologyWidget::on_shapeComboBox_currentIndexChanged(int index)
{
    emitSignal();
}

void MorphologyWidget::on_widthSpin_valueChanged(int arg1)
{
    ui->anchorXSpin->setMaximum(arg1-1);
    emitSignal();
}

void MorphologyWidget::on_heightSpin_valueChanged(int arg1)
{
    ui->anchorYSpin->setMaximum(arg1-1);
    emitSignal();
}

void MorphologyWidget::on_anchorXSpin_valueChanged(int arg1)
{
    emitSignal();
}

void MorphologyWidget::on_anchorYSpin_valueChanged(int arg1)
{
    emitSignal();
}

void MorphologyWidget::on_iterSpin_valueChanged(int arg1)
{
    emitSignal();
}

void MorphologyWidget::on_borderTypeCombo_currentIndexChanged(int index)
{
    emitSignal();
}

void MorphologyWidget::on_borderValueEdit_editingFinished()
{
    emitSignal();
}

void MorphologyWidget::emitSignal()
{
    QStringList values=ui->borderValueEdit->text().split(",");
    cv::Scalar borderVals=cv::Scalar::all(0);
    for(int i=0;i<values.size()&&i<4;++i){
        borderVals[i]=QString(values.at(i)).toDouble();
    }
    emit argsChanged(ui->morphTypeCombo->currentIndex(),ui->shapeComboBox->currentIndex(),ui->widthSpin->value(),ui->heightSpin->value(),
                     ui->anchorXSpin->value(),ui->anchorYSpin->value(),ui->iterSpin->value(),ui->borderTypeCombo->currentIndex(),borderVals);
}
