#include "FILE_WIDGET_AUTO_REPLACED.h"
#include "ui_FILE_WIDGET_AUTO_REPLACED.h"

PLUGIN_WIDGET_AUTO_REPLACED::PLUGIN_WIDGET_AUTO_REPLACED(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PLUGIN_WIDGET_AUTO_REPLACED)
{
    ui->setupUi(this);
}

PLUGIN_WIDGET_AUTO_REPLACED::~PLUGIN_WIDGET_AUTO_REPLACED()
{
    delete ui;
}
