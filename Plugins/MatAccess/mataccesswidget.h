#ifndef MATACCESSWIDGET_H
#define MATACCESSWIDGET_H

#include <QWidget>

namespace Ui {
class MatAccessWidget;
}

class MatAccessWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatAccessWidget(QWidget *parent = 0);
    void setMaximum(int ax,int bx,int cx);
    void setDepthLabel(QString text);
    ~MatAccessWidget();
signals:
    void internalArgsChanged(int a,int b,int c);

private slots:
    void on_rowSpin_valueChanged(int arg1);

    void on_colSpin_valueChanged(int arg1);

    void on_channelSpin_valueChanged(int arg1);

private:
    Ui::MatAccessWidget *ui;
};

#endif // MatAccessWidget_H
