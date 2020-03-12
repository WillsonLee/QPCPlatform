#ifndef BLOBCLUSTERWIDGET_H
#define BLOBCLUSTERWIDGET_H

#include <QWidget>

namespace Ui {
class BlobClusterWidget;
}

class BlobClusterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BlobClusterWidget(QWidget *parent = 0);
    void initArgs(bool fourNeighbors, int outType, int algorithm, bool removal, int area);
    ~BlobClusterWidget();
signals:
    void internalArgsChanged(bool fourNeighbors,int outType,int algorithm,bool removal,int area);

private slots:
    void on_fourRadioButton_toggled(bool checked);

    void on_depthComboBox_currentIndexChanged(int index);

    void on_speckleCheckBox_toggled(bool checked);

    void on_areaSpinBox_valueChanged(int arg1);

    void on_algorithmComboBox_currentIndexChanged(int index);

private:
    Ui::BlobClusterWidget *ui;
    bool fourNeighbors;
    bool removal;
};

#endif // BlobClusterWidget_H
