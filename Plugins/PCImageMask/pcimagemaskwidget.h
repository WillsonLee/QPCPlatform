#ifndef PCIMAGEMASKWIDGET_H
#define PCIMAGEMASKWIDGET_H

#include <QWidget>

namespace Ui {
class PCImageMaskWidget;
}

class PCImageMaskWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PCImageMaskWidget(QWidget *parent = 0);
    void initArgs(bool autoOffset, bool autoGSD);
    void setMode(bool binary);
    void setInverse(bool inverse);
    void setAutoParas(double x,double y,double gsd);
    ~PCImageMaskWidget();
signals:
    void argsChanged(double x,double y,double gsd,bool autoOffset,bool autoGSD);
    void modeChanged(bool binary);
    void inverseStateChanged(bool inversed);

private slots:
    void on_offsetCheckBox_toggled(bool checked);

    void on_gsdCheckBox_toggled(bool checked);

    void on_xOffsetEdit_editingFinished();

    void on_yOffsetEdit_editingFinished();

    void on_gsdEdit_editingFinished();

    void on_radioButtonMulti_toggled(bool checked);

    void on_inverseCheckBox_toggled(bool checked);

private:
    Ui::PCImageMaskWidget *ui;
private:
    void sendSignal();
};

#endif // PCImageMaskWidget_H
