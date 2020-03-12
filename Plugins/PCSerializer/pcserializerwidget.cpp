#include "pcserializerwidget.h"
#include "ui_pcserializerwidget.h"
#include <QFileDialog>

PCSerializerWidget::PCSerializerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PCSerializerWidget)
{
    ui->setupUi(this);
    connect(ui->lineEdit,&QLineEdit::textChanged,this,[=](QString text){
        emit folderChanged(text);
    });
}

void PCSerializerWidget::initFolder(QString folderName)
{
    ui->lineEdit->setText(folderName.replace("\\","/"));
}

PCSerializerWidget::~PCSerializerWidget()
{
    delete ui;
}

void PCSerializerWidget::on_pushButton_clicked()
{
    QString path=QFileDialog::getExistingDirectory(this,tr("select a existing path to save files"),ui->lineEdit->text());
    if(path!=""&&path!=ui->lineEdit->text()){
        ui->lineEdit->setText(path.replace("\\","/"));
    }
}
