#ifndef INTROPAGEWIDGET_H
#define INTROPAGEWIDGET_H

#include <QWidget>

namespace Ui {
class IntroPageWidget;
}
/**
 * @brief The IntroPageWidget class 新建插件向导第一页(设置插件名称与路径)界面类
 */
class IntroPageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IntroPageWidget(QWidget *parent = 0);
    void initText(QString name,QString path);
    QString getProjectName();
    QString getProjectPath();
    ~IntroPageWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::IntroPageWidget *ui;
};

#endif // INTROPAGEWIDGET_H
