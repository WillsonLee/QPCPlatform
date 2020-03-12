#ifndef THREEDTOMATWIDGET_H
#define THREEDTOMATWIDGET_H

#include <QWidget>

namespace Ui {
class ThreeDToMatWidget;
}

class ThreeDToMatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ThreeDToMatWidget(QWidget *parent = 0);
    void initParameters(double GSD, int mode);
    ~ThreeDToMatWidget();
signals:
    void internalArgsChanged(double GSD,int mode);

private slots:
    void on_lineEdit_editingFinished();

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::ThreeDToMatWidget *ui;
    double GSD;
};

#endif // ThreeDToMatWidget_H
