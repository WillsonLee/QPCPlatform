#ifndef SPACIALCLUSTERWIDGET_H
#define SPACIALCLUSTERWIDGET_H

#include <QWidget>

namespace Ui {
class SpacialClusterWidget;
}

class SpacialClusterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SpacialClusterWidget(QWidget *parent = 0);
    void setArgs(bool tolAuto,double tol);
    ~SpacialClusterWidget();
signals:
    void argsChanged(bool tolAuto,double tol);

private slots:
    void on_tolCheckBox_toggled(bool checked);

    void on_tolLineEdit_editingFinished();

private:
    Ui::SpacialClusterWidget *ui;
};

#endif // SpacialClusterWidget_H
