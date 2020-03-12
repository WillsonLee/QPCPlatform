#include "mattofilewidget.h"
#include "ui_mattofilewidget.h"
#include <QFileDialog>

MatToFileWidget::MatToFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatToFileWidget)
{
    ui->setupUi(this);
}

void MatToFileWidget::initParas(QString name, QString path)
{
    ui->nameLineEdit->setText(name);
    ui->pathLineEdit->setText(path);
}

MatToFileWidget::~MatToFileWidget()
{
    delete ui;
}

void MatToFileWidget::on_okButton_clicked()
{
    emit requestAction(ui->nameLineEdit->text(),ui->pathLineEdit->text());
}

void MatToFileWidget::on_pathButton_clicked()
{
    QString path=QFileDialog::getExistingDirectory(this,tr("open dependency path"));
    if(path!=""&&path!=ui->pathLineEdit->text()){
        ui->pathLineEdit->setText(path);
    }
}
