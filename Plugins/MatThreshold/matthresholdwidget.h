#ifndef MATTHRESHOLDWIDGET_H
#define MATTHRESHOLDWIDGET_H

#include <QWidget>
#include <QVector>

namespace Ui {
class MatThresholdWidget;
}

class MatThresholdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatThresholdWidget(QWidget *parent = 0);
    void initArgs(double thresh,double max_value,QString type);
    void resetSelection(QList<QString> items);
    ~MatThresholdWidget();
signals:
    void internalArgsChanged(double thresh,double max_value,QString type);

private slots:
    void on_typesCombo_currentIndexChanged(int index);

    void on_maxSpin_valueChanged(int arg1);

    void on_threshEdit_editingFinished();

private:
    Ui::MatThresholdWidget *ui;
    double thresh;
    double max_value;
    QVector<QString> types;
    QString type;
};

#endif // MatThresholdWidget_H
