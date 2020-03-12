#ifndef AXTOBTHPLUSCWIDGET_H
#define AXTOBTHPLUSCWIDGET_H

#include <QWidget>

namespace Ui {
class AXToBthPlusCWidget;
}

class AXToBthPlusCWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AXToBthPlusCWidget(QWidget *parent = 0);
    void initParameters(double a,double b,double c);
    ~AXToBthPlusCWidget();
signals:
    void internalArgsChanged(double a,double b,double c);

private slots:
    void on_okButton_clicked();

    void on_resetButton_clicked();

private:
    Ui::AXToBthPlusCWidget *ui;
    double m_a,m_b,m_c;
    void setDisplay(double a,double b,double c);
};

#endif // AXToBthPlusCWidget_H
