#ifndef MATLOADERWIDGET_H
#define MATLOADERWIDGET_H

#include <QWidget>
#include <QMap>

namespace Ui {
class MatLoaderWidget;
}

class MatLoaderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatLoaderWidget(QWidget *parent = 0);
    void initParas(std::string fileName,int mode);
    ~MatLoaderWidget();
signals:
    void internalArgsChanged(std::string fileName,int mode);

private slots:
    void on_openPushButton_clicked();

    void on_modeComboBox_currentIndexChanged(int index);

private:
    Ui::MatLoaderWidget *ui;
    QMap<int,int> mapIndexToMode;
    QMap<int,int> mapModeToIndex;
};

#endif // MatLoaderWidget_H
