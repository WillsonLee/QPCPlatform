#ifndef PCDLOADERWIDGET_H
#define PCDLOADERWIDGET_H

#include <QWidget>

namespace Ui {
class PCDLoaderWidget;
}

class PCDLoaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PCDLoaderWidget(QWidget *parent = 0);
    void initParameters(QString name,int type);
    ~PCDLoaderWidget();
signals:
    void internalArgsChanged(QString name,int type);

private slots:
    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::PCDLoaderWidget *ui;
};

#endif // PCDLoaderWidget_H
