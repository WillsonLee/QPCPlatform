#include "matthresholdwidget.h"
#include "ui_matthresholdwidget.h"
#include <QList>
#include <QRegExp>
#include <QRegExpValidator>

MatThresholdWidget::MatThresholdWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatThresholdWidget)
{
    ui->setupUi(this);
    ui->threshEdit->setValidator(new QRegExpValidator(QRegExp("^[-]?[0-9]+[\.]?[0-9]*$")));
}

void MatThresholdWidget::initArgs(double thresh, double max_value, QString type)
{
    ui->threshEdit->setText(QString::number(thresh));
    ui->maxSpin->setValue((int)max_value);
    ui->typesCombo->setCurrentText(type);
}

void MatThresholdWidget::resetSelection(QList<QString> items)
{
    types.clear();
    for(int i=0;i<items.size();++i){
        types.push_back(items[i]);
    }
    QStringList list;
    for(auto item:types){
        list<<item;
    }
    ui->typesCombo->clear();
    ui->typesCombo->addItems(list);
    if(ui->typesCombo->currentIndex()>=types.size()){
        ui->typesCombo->setCurrentIndex(0);
    }
}

MatThresholdWidget::~MatThresholdWidget()
{
    delete ui;
}

void MatThresholdWidget::on_typesCombo_currentIndexChanged(int index)
{
    emit internalArgsChanged(ui->threshEdit->text().toDouble(),ui->maxSpin->value(),ui->typesCombo->currentText());
}

void MatThresholdWidget::on_maxSpin_valueChanged(int arg1)
{
    emit internalArgsChanged(ui->threshEdit->text().toDouble(),arg1,ui->typesCombo->currentText());
}

void MatThresholdWidget::on_threshEdit_editingFinished()
{
    emit internalArgsChanged(ui->threshEdit->text().toDouble(),ui->maxSpin->value(),ui->typesCombo->currentText());
}
