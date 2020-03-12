#include "spacialclusterwidget.h"
#include "ui_spacialclusterwidget.h"

SpacialClusterWidget::SpacialClusterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpacialClusterWidget)
{
    ui->setupUi(this);
    ui->tolLineEdit->setValidator(new QRegExpValidator(QRegExp("^[-]?[0-9]+[\.]?[0-9]*$")));
}

void SpacialClusterWidget::setArgs(bool tolAuto, double tol)
{
    ui->tolCheckBox->setChecked(tolAuto);
    ui->tolLineEdit->setText(QString::number(tol));
}

SpacialClusterWidget::~SpacialClusterWidget()
{
    delete ui;
}

void SpacialClusterWidget::on_tolCheckBox_toggled(bool checked)
{
    ui->tolLineEdit->setEnabled(!checked);
    emit argsChanged(checked,ui->tolLineEdit->text().toDouble());
}

void SpacialClusterWidget::on_tolLineEdit_editingFinished()
{
    emit argsChanged(ui->tolCheckBox->isChecked(),ui->tolLineEdit->text().toDouble());
}
