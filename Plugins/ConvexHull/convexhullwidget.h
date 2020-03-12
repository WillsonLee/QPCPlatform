#ifndef CONVEXHULLWIDGET_H
#define CONVEXHULLWIDGET_H

#include <QWidget>

namespace Ui {
class ConvexHullWidget;
}

class ConvexHullWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConvexHullWidget(QWidget *parent = 0);
    void initArgs(bool binary,int algo);
    ~ConvexHullWidget();
signals:
    void argsChanged(bool binary,int algo);

private slots:
    void on_binaryRadio_toggled(bool checked);

    void on_comboBox_currentIndexChanged(int index);

private:
    Ui::ConvexHullWidget *ui;
};

#endif // ConvexHullWidget_H
