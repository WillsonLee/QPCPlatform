#include "loopcontrolwidget.h"
#include "ui_loopcontrolwidget.h"

LoopControlWidget::LoopControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoopControlWidget)
{
    ui->setupUi(this);
    connect(this,&LoopControlWidget::runningStateChanged,ui->startButton,[=](bool running){
        ui->startButton->setEnabled(!running);
    });
    connect(this,&LoopControlWidget::runningStateChanged,ui->stopButton,[=](bool running){
        ui->stopButton->setEnabled(running);
    });
    connect(this,&LoopControlWidget::runningStateChanged,ui->totalSpinBox,[=](bool running){
        ui->totalSpinBox->setEnabled(!running);
    });
    connect(this,&LoopControlWidget::progressChanged,ui->progressBar,&QProgressBar::setValue);
    ui->lcdNumber->setGeometry(QRect(ui->lcdNumber->geometry().left(),ui->lcdNumber->geometry().top(),ui->lcdNumber->width(),ui->startButton->height()));
}

void LoopControlWidget::initParameters(bool isRunning, int current, int total)
{
    setRunning(isRunning);
    ui->totalSpinBox->setValue(total);
    setCurrentCount(current);
}

void LoopControlWidget::setCurrentCount(int current)
{
    if(current==-1){
        setRunning(false);//跑完了
    }
    else{
        ui->lcdNumber->display(current);
        int newVal=int(float(current)/ui->totalSpinBox->value()*100);
        if(newVal!=ui->progressBar->value()){
            emit progressChanged(newVal);
        }
    }
}

LoopControlWidget::~LoopControlWidget()
{
    delete ui;
}

void LoopControlWidget::on_startButton_clicked()
{
    setRunning(true);
}

void LoopControlWidget::on_stopButton_clicked()
{
    setRunning(false);
}

void LoopControlWidget::setRunning(bool value)
{
    if(running!=value)emit runningStateChanged(value);
    running = value;
}

void LoopControlWidget::on_totalSpinBox_valueChanged(int arg1)
{
    emit totalCountChanged(arg1);
}
