#include "axtobthpluscwidget.h"
#include "ui_axtobthpluscwidget.h"
#include <QRegExp>
#include <QValidator>
#include <QRegExpValidator>

AXToBthPlusCWidget::AXToBthPlusCWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AXToBthPlusCWidget)
{
    ui->setupUi(this);
    QRegExp ex("^[-]?[0-9]+[\.]?[0-9]*");
    QValidator *val=new QRegExpValidator(ex);
    ui->aLineEdit->setValidator(val);
    ui->bLineEdit->setValidator(val);
    ui->cLineEdit->setValidator(val);
}

void AXToBthPlusCWidget::initParameters(double a, double b, double c)
{
    m_a=a;
    m_b=b;
    m_c=c;
    this->on_resetButton_clicked();
    this->setDisplay(a,b,c);
}

AXToBthPlusCWidget::~AXToBthPlusCWidget()
{
    delete ui;
}

void AXToBthPlusCWidget::on_okButton_clicked()
{
    this->setDisplay(ui->aLineEdit->text().toDouble(),ui->bLineEdit->text().toDouble(),ui->cLineEdit->text().toDouble());
    emit internalArgsChanged(ui->aLineEdit->text().toDouble(),ui->bLineEdit->text().toDouble(),ui->cLineEdit->text().toDouble());
}

void AXToBthPlusCWidget::on_resetButton_clicked()
{
    ui->aLineEdit->setText(QString::number(m_a));
    ui->bLineEdit->setText(QString::number(m_b));
    ui->cLineEdit->setText(QString::number(m_c));
    this->setDisplay(m_a,m_b,m_c);
    emit internalArgsChanged(m_a,m_b,m_c);
}

void AXToBthPlusCWidget::setDisplay(double a, double b, double c)
{
    QString txt="Calculate: y="+QString::number(a)+"*x^"+QString::number(b);
    if(c!=0)txt+=(c>=0?"+":"-")+QString::number(abs(c));
    ui->displayLabel->setText(txt);
}
