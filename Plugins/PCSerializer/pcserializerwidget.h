#ifndef PCSERIALIZERWIDGET_H
#define PCSERIALIZERWIDGET_H

#include <QWidget>

namespace Ui {
class PCSerializerWidget;
}

class PCSerializerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PCSerializerWidget(QWidget *parent = 0);
    void initFolder(QString folderName);
    ~PCSerializerWidget();
signals:
    void folderChanged(QString folderName);

private slots:
    void on_pushButton_clicked();

private:
    Ui::PCSerializerWidget *ui;
};

#endif // PCSerializerWidget_H
