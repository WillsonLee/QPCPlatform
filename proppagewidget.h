#ifndef PROPPAGEWIDGET_H
#define PROPPAGEWIDGET_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class PropPageWidget;
}
/**
 * @brief The PropPageWidget class 新建插件向导第二页(设置插件属性页)界面类
 */
class PropPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PropPageWidget(QWidget *parent = 0);
    void initProps(bool hasWidget,bool embeded,int num_in,int num_out,
                   QString includePath,QString dependPath);
    void getProps(bool &hasWidget, bool &embeded, int &num_in, int &num_out,
                  QString &includePath, QString &dependPath,
                  QVector<QString> &input_types, QVector<QString> &out_types,
                  QVector<QString> &input_doc, QVector<QString> &out_doc, QString &plugin_doc);
    ~PropPageWidget();

private slots:
    void on_hasWidgetCheckBox_toggled(bool checked);

    void on_numInputSpinBox_valueChanged(int arg1);

    void on_numOutSpinBox_valueChanged(int arg1);

    void on_includePushButton_clicked();

    void on_dependPushButton_clicked();

private:
    Ui::PropPageWidget *ui;
    QVector<QString> input_types;
    QVector<QString> out_types;
    QVector<QString> input_doc;
    QVector<QString> out_doc;
private:
    void initInputTable(int num);
    void initOutputTable(int num);
    void initTable(QTableWidget *table, int num, bool isInputTable);
};

#endif // PROPPAGEWIDGET_H
