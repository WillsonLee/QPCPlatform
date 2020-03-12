#ifndef MATTOFILEWIDGET_H
#define MATTOFILEWIDGET_H

#include <QWidget>

namespace Ui {
class MatToFileWidget;
}

class MatToFileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MatToFileWidget(QWidget *parent = 0);
    void initParas(QString name,QString path);
    ~MatToFileWidget();
signals:
    void requestAction(QString name,QString path);

private slots:
    void on_okButton_clicked();

    void on_pathButton_clicked();

private:
    Ui::MatToFileWidget *ui;
};

#endif // MatToFileWidget_H
