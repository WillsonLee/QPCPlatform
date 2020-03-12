#include "intropagewidget.h"
#include "ui_intropagewidget.h"
#include <QFileDialog>

IntroPageWidget::IntroPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntroPageWidget)
{
    ui->setupUi(this);
    QRegExp proReg("^[0-9a-zA-Z_]+$");
    QValidator *proVal=new QRegExpValidator(proReg);
    ui->nameLineEdit->setValidator(proVal);
    QRegExp pathReg("^[0-9a-zA-Z_-/\\\.:]+$");
    QValidator *pathVal=new QRegExpValidator(pathReg);
    ui->pathLineEdit->setValidator(pathVal);
}

void IntroPageWidget::initText(QString name, QString path)
{
    ui->nameLineEdit->setText(name);
    ui->pathLineEdit->setText(path);
}

QString IntroPageWidget::getProjectName()
{
    return ui->nameLineEdit->text();
}

QString IntroPageWidget::getProjectPath()
{
    return ui->pathLineEdit->text();
}

IntroPageWidget::~IntroPageWidget()
{
    delete ui;
}

void IntroPageWidget::on_pushButton_clicked()
{
    QString dirName=QFileDialog::getExistingDirectory(this,tr("open directory"),ui->pathLineEdit->text());
    if(dirName!=""){
        ui->pathLineEdit->setText(dirName);
    }
}
