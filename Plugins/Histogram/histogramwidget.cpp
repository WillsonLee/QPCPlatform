#include "histogramwidget.h"
#include "ui_histogramwidget.h"
#include <QRegExpValidator>
#include <QRegExp>

HistogramWidget::HistogramWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistogramWidget)
{
    ui->setupUi(this);
    ui->lineEditMin1->setValidator(new QRegExpValidator(QRegExp("^[-]?[0-9]+[\.]?[0-9]*$")));
    ui->lineEditMin2->setValidator(new QRegExpValidator(QRegExp("^[-]?[0-9]+[\.]?[0-9]*$")));
    ui->lineEditMax1->setValidator(new QRegExpValidator(QRegExp("^[-]?[0-9]+[\.]?[0-9]*$")));
    ui->lineEditMax2->setValidator(new QRegExpValidator(QRegExp("^[-]?[0-9]+[\.]?[0-9]*$")));
    setTotalChannels(2);
    connect(ui->radioButtonLeft,&QRadioButton::clicked,this,&HistogramWidget::binsEdgeSelect);
    connect(ui->radioButtonMiddle,&QRadioButton::clicked,this,&HistogramWidget::binsEdgeSelect);
    connect(ui->radioButtonRight,&QRadioButton::clicked,this,&HistogramWidget::binsEdgeSelect);
}

void HistogramWidget::initArgs(int channels, bool norm, bool accumulate, int bins1, float min1, float max1, int bins2, float min2, float max2)
{
    ui->spinBoxChannels->setValue(channels);
    if(channels==1){
        ui->groupBox_2->setEnabled(false);
    }
    ui->checkBoxNorm->setChecked(norm);
    ui->checkBoxAccumu->setChecked(accumulate);
    ui->spinBoxBins1->setValue(bins1);
    ui->lineEditMin1->setText(QString::number(min1));
    ui->lineEditMax1->setText(QString::number(max1));
    ui->spinBoxBins2->setValue(bins2);
    ui->lineEditMin2->setText(QString::number(min2));
    ui->lineEditMax2->setText(QString::number(max2));
}

void HistogramWidget::setBinsEdge(int edge)
{
    switch (edge) {
    case 0:
        ui->radioButtonLeft->setChecked(true);
        ui->radioButtonMiddle->setChecked(false);
        ui->radioButtonRight->setChecked(false);
        break;
    case 1:
        ui->radioButtonLeft->setChecked(false);
        ui->radioButtonMiddle->setChecked(true);
        ui->radioButtonRight->setChecked(false);
        break;
    default:
        ui->radioButtonLeft->setChecked(false);
        ui->radioButtonMiddle->setChecked(false);
        ui->radioButtonRight->setChecked(true);
        break;
    }
}

void HistogramWidget::setTotalChannels(int num)
{
    int chan1=ui->comboBoxChannel1->currentIndex();
    int chan2=ui->comboBoxChannel2->currentIndex();
    ui->comboBoxChannel1->clear();
    ui->comboBoxChannel2->clear();
    QStringList list;
    for(int i=0;i<num;++i){
        list<<"channel"+QString::number(i+1);
    }
    ui->comboBoxChannel1->addItems(list);
    ui->comboBoxChannel2->addItems(QStringList(list));
    if(chan1<0||chan1>=num){
        ui->comboBoxChannel1->setCurrentIndex(0);
    }
    else{
        ui->comboBoxChannel1->setCurrentIndex(chan1);
    }
    if(chan2<0||chan2>=num){
        if(num>1){
            ui->comboBoxChannel2->setCurrentIndex(1);
        }
        else{
           ui->comboBoxChannel2->setCurrentIndex(0);
        }
    }
    else{
        ui->comboBoxChannel2->setCurrentIndex(chan2);
    }
}

void HistogramWidget::setAutoMinMax(bool auto1, bool auto2)
{
    ui->checkBoxAuto1->setChecked(auto1);
    ui->checkBoxAuto2->setChecked(auto2);
}

HistogramWidget::~HistogramWidget()
{
    delete ui;
}

void HistogramWidget::on_spinBoxChannels_valueChanged(int arg1)
{
    if(arg1>1){
        ui->groupBox_2->setEnabled(true);
    }
    else{
        ui->groupBox_2->setEnabled(false);
    }
    sendSignal();
}

void HistogramWidget::on_checkBoxNorm_toggled(bool checked)
{
    sendSignal();
}

void HistogramWidget::on_checkBoxAccumu_toggled(bool checked)
{
    sendSignal();
}

void HistogramWidget::on_spinBoxBins1_valueChanged(int arg1)
{
    sendSignal();
}

void HistogramWidget::on_lineEditMin1_editingFinished()
{
    sendSignal();
}

void HistogramWidget::on_lineEditMax1_editingFinished()
{
    sendSignal();
}

void HistogramWidget::on_spinBoxBins2_valueChanged(int arg1)
{
    sendSignal();
}

void HistogramWidget::on_lineEditMin2_editingFinished()
{
    sendSignal();
}

void HistogramWidget::on_lineEditMax2_editingFinished()
{
    sendSignal();
}

void HistogramWidget::sendSignal()
{
    emit internalArgsChanged(ui->spinBoxChannels->value(),ui->checkBoxNorm->isChecked(),ui->checkBoxAccumu->isChecked(),
                             ui->spinBoxBins1->value(),ui->lineEditMin1->text().toFloat(),ui->lineEditMax1->text().toFloat(),
                             ui->spinBoxBins2->value(),ui->lineEditMin2->text().toFloat(),ui->lineEditMax2->text().toFloat());
}

void HistogramWidget::on_comboBoxChannel1_currentIndexChanged(int index)
{
    emit channelsChanged(ui->comboBoxChannel1->currentIndex(),ui->comboBoxChannel2->currentIndex());
}

void HistogramWidget::on_comboBoxChannel2_currentIndexChanged(int index)
{
    emit channelsChanged(ui->comboBoxChannel1->currentIndex(),ui->comboBoxChannel2->currentIndex());
}

void HistogramWidget::binsEdgeSelect()
{
    int edge;
    if(ui->radioButtonLeft->isChecked()){
        edge=0;
    }
    else if(ui->radioButtonMiddle->isChecked()){
        edge=1;
    }
    else{
        edge=2;
    }
    emit binsEdgeChanged(edge);
}

void HistogramWidget::on_checkBoxAuto1_toggled(bool checked)
{
    ui->lineEditMin1->setEnabled(!checked);
    ui->lineEditMax1->setEnabled(!checked);
    emit binsRangeAutoChanged(ui->checkBoxAuto1->isChecked(),ui->checkBoxAuto2->isChecked());
}

void HistogramWidget::on_checkBoxAuto2_toggled(bool checked)
{
    ui->lineEditMin2->setEnabled(!checked);
    ui->lineEditMax2->setEnabled(!checked);
    emit binsRangeAutoChanged(ui->checkBoxAuto1->isChecked(),ui->checkBoxAuto2->isChecked());
}
