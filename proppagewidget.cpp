#include "proppagewidget.h"
#include "ui_proppagewidget.h"
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QComboBox>
#include <typenamedisplayer.h>
#include <QDebug>

PropPageWidget::PropPageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropPageWidget)
{
    ui->setupUi(this);
    QRegExp pathReg("^[0-9a-zA-Z_-/\\\.:]+$");
    QValidator *pathVal=new QRegExpValidator(pathReg);
    ui->includeLineEdit->setValidator(pathVal);
    ui->dependLineEdit->setValidator(pathVal);
}

void PropPageWidget::initProps(bool hasWidget, bool embeded, int num_in, int num_out, QString includePath, QString dependPath)
{
    ui->hasWidgetCheckBox->setChecked(hasWidget);
    ui->embededCheckBox->setChecked(embeded);
    ui->numInputSpinBox->setValue(num_in);
    ui->numOutSpinBox->setValue(num_out);
    ui->includeLineEdit->setText(includePath);
    ui->dependLineEdit->setText(dependPath);
}

void PropPageWidget::getProps(bool &hasWidget, bool &embeded, int &num_in, int &num_out, QString &includePath, QString &dependPath, QVector<QString> &input_types, QVector<QString> &out_types, QVector<QString> &input_doc, QVector<QString> &out_doc,QString &plugin_doc)
{
    hasWidget=ui->hasWidgetCheckBox->isChecked();
    embeded=ui->embededCheckBox->isChecked();
    num_in=ui->numInputSpinBox->value();
    num_out=ui->numOutSpinBox->value();
    includePath=ui->includeLineEdit->text();
    dependPath=ui->dependLineEdit->text();
    //input_type,out_types,input_doc,out_doc根据表格确定
    input_types.clear();
    input_doc.clear();
    for(int i=0;i<ui->numInputSpinBox->value();++i){
        input_types.push_back(this->input_types[i]);
        input_doc.push_back(this->input_doc[i]);
    }
    out_types.clear();
    out_doc.clear();
    for(int i=0;i<ui->numOutSpinBox->value();++i){
        out_types.push_back(this->out_types[i]);
        out_doc.push_back(this->out_doc[i]);
    }
    plugin_doc=ui->pluginDescriptionLineEdit->text();
}

PropPageWidget::~PropPageWidget()
{
    delete ui;
}

void PropPageWidget::on_hasWidgetCheckBox_toggled(bool checked)
{
    ui->embededCheckBox->setEnabled(checked);
}

void PropPageWidget::on_numInputSpinBox_valueChanged(int arg1)
{
    this->initInputTable(arg1);
}

void PropPageWidget::on_numOutSpinBox_valueChanged(int arg1)
{
    this->initOutputTable(arg1);
}

void PropPageWidget::initInputTable(int num)
{
    QTableWidget *table=ui->inputsTableWidget;
    this->input_types.resize(num);
    this->input_doc.resize(num);
    this->initTable(table,num,true);
}

void PropPageWidget::initOutputTable(int num)
{
    QTableWidget *table=ui->outsTableWidget;
    this->out_types.resize(num);
    this->out_doc.resize(num);
    this->initTable(table,num,false);
}

void PropPageWidget::initTable(QTableWidget *table, int num,bool isInputTable)
{
    table->clear();
    table->setColumnCount(2);
    table->setRowCount(num);
    table->setHorizontalHeaderItem(0,new QTableWidgetItem(tr("data type")));
    table->setHorizontalHeaderItem(1,new QTableWidgetItem(tr("description")));
    for(int i=0;i<num;++i){
        QComboBox *combo=new QComboBox();
        combo->setEditable(true);
        combo->addItems(TypeNameDisplayer::allDisplayTypeStrings());
        table->setCellWidget(i,0,combo);
        connect(combo,&QComboBox::currentTextChanged,this,[=](QString text){
             if(isInputTable){
                this->input_types[i]=text;
             }
             else{
                this->out_types[i]=text;
             }
        });
        combo->setCurrentIndex(0);
        if(isInputTable){
            this->input_types[i]=combo->currentText();
        }
        else{
            this->out_types[i]=combo->currentText();
        }
        QTableWidgetItem *it2=new QTableWidgetItem();
        table->setItem(i,1,it2);
    }
    connect(table,&QTableWidget::cellChanged,this,[=](int row,int col){
        if(isInputTable){
            this->input_doc[row]=ui->inputsTableWidget->item(row,col)->text();
        }
        else{
            this->out_doc[row]=ui->outsTableWidget->item(row,col)->text();
        }
    });
    for(int i=0;i<table->columnCount();++i){
        table->horizontalHeader()->setSectionResizeMode(i,QHeaderView::ResizeToContents);
    }
}

void PropPageWidget::on_includePushButton_clicked()
{
    QString dirName=QFileDialog::getExistingDirectory(this,tr("open include path"),ui->includeLineEdit->text());
    if(dirName!=""&&dirName!=ui->includeLineEdit->text()){
        ui->includeLineEdit->setText(dirName);
    }
}

void PropPageWidget::on_dependPushButton_clicked()
{
    QString dirName=QFileDialog::getExistingDirectory(this,tr("open dependency path"),ui->dependLineEdit->text());
    if(dirName!=""&&dirName!=ui->includeLineEdit->text()){
        ui->dependLineEdit->setText(dirName);
    }
}
