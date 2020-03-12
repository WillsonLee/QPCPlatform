#ifndef MINBOUNDINGBOXWIDGET_H
#define MINBOUNDINGBOXWIDGET_H

#include <QWidget>

namespace Ui {
class MinBoundingBoxWidget;
}

class MinBoundingBoxWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MinBoundingBoxWidget(QWidget *parent = 0);
    void initArgs(bool binary,bool merge,int node);
    ~MinBoundingBoxWidget();
signals:
    void internalArgsChanged(bool binary,bool merge,int node);

private slots:
    void on_radioButtonBinary_toggled(bool checked);

    void on_checkBoxMerge_toggled(bool checked);

    void on_nodeSpinBox_valueChanged(int arg1);

private:
    Ui::MinBoundingBoxWidget *ui;
};

#endif // MinBoundingBoxWidget_H
