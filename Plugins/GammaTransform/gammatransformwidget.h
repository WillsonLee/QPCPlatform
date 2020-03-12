#ifndef GAMMATRANSFORMWIDGET_H
#define GAMMATRANSFORMWIDGET_H

#include <QWidget>

namespace Ui {
class GammaTransformWidget;
}

class GammaTransformWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GammaTransformWidget(QWidget *parent = 0);
    void initArgs(double gamma);
    ~GammaTransformWidget();
signals:
    void internalArgsChanged(double gamma);

private slots:
    void on_doubleSpinBox_valueChanged(double arg1);

private:
    Ui::GammaTransformWidget *ui;
    double gamma;
};

#endif // GammaTransformWidget_H
