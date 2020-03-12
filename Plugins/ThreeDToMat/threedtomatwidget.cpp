#include "threedtomatwidget.h"
#include "ui_threedtomatwidget.h"
#include <QRegExp>
#include <QValidator>
#include <QRegExpValidator>

ThreeDToMatWidget::ThreeDToMatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThreeDToMatWidget)
{
    ui->setupUi(this);
    QValidator *val=new QRegExpValidator(QRegExp("^[-]?[0-9]+[\.]?[0-9]*$"));
    ui->lineEdit->setValidator(val);
    QStringList list;
    list<<"PointCount"<<"HeightDiif";
    ui->comboBox->addItems(list);
}

void ThreeDToMatWidget::initParameters(double GSD,int mode)
{
    this->GSD=GSD;
    ui->lineEdit->setText(QString::number(GSD));
    ui->comboBox->setCurrentIndex(mode);
}

ThreeDToMatWidget::~ThreeDToMatWidget()
{
    delete ui;
}

void ThreeDToMatWidget::on_lineEdit_editingFinished()
{
    double gsd=ui->lineEdit->text().toDouble();
    if(gsd!=this->GSD){
        this->GSD=gsd;
        emit internalArgsChanged(gsd,ui->comboBox->currentIndex());
    }
}

void ThreeDToMatWidget::on_comboBox_currentIndexChanged(int index)
{
    emit internalArgsChanged(this->GSD,ui->comboBox->currentIndex());
}
