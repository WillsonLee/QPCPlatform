#ifndef LOOPCONTROLWIDGET_H
#define LOOPCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class LoopControlWidget;
}

class LoopControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoopControlWidget(QWidget *parent = 0);
    void initParameters(bool isRunning,int current,int total);
    void setCurrentCount(int current);
    ~LoopControlWidget();
    void setRunning(bool value);

signals:
    //    void internalArgsChanged(int a,int b,int c);
    void runningStateChanged(bool running);
    void totalCountChanged(int count);
    void progressChanged(int value);//传递给progressBar的信号

private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_totalSpinBox_valueChanged(int arg1);

private:
    Ui::LoopControlWidget *ui;
    bool running;
};

#endif // LoopControlWidget_H
