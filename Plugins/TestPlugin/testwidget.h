#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>

namespace Ui {
class TestWidget;
}

class TestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TestWidget(QWidget *parent = 0);
    void setInitialParas(int a,int b,int c);
    ~TestWidget();
signals:
    void internalArgsChanged(int a,int b,int c);

private slots:
    void on_aSlider_valueChanged(int value);

    void on_bSlider_valueChanged(int value);

    void on_cSlider_valueChanged(int value);

private:
    Ui::TestWidget *ui;
};

#endif // TESTWIDGET_H
