#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>
#include <shell.h>
#include <flow.h>
#include <reflex.h>
#include <vector>
#include <string>
#include <QPaintEvent>
#include <QButtonGroup>
#include <QWizard>
#include <QWizardPage>
#include <opencv2/opencv.hpp>
#include <QLibrary>

//};
/**\brief 插件以及系统配置信息类
*/
class Property
{
private:
    QMap<QString,QString> properties;
public:
    void setProperty(QString name,QString value);
    QString getProperty(QString name,QString defaultValue);
    QString getProperty(QString name);
    bool propertyExist(QString name);
    QString getAllInfo();
};
//该类为MainWindow类中的instanceCount对象定制,当做QMap用但同时使其能够接受信号;
//instanceCount用于对每一个插件类的实例计数,在新建与删除Shell类对象时更改相应的计数,即接受相应的信号作出改变
template<class key,class T>
class CountingMap:public QObject,public QMap<key,T>{};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    bool eventFilter(QObject *watched, QEvent *event);
    ~MainWindow();
private slots:
    void on_actionToolBox_toggled(bool arg1);

    void on_toolBox_visibilityChanged(bool visible);

    void on_workspaceDock_visibilityChanged(bool visible);

    void on_actiondoc_triggered();

    void on_actiontutorial_triggered();

    void on_actionLoad_L_triggered();

    void on_actionNew_N_triggered();

    void on_actionOutputs_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    std::vector<std::string> *all_plugins;//所有插件的名称
    //sys有的属性:"rootPath","pluginPathCount","folder"+序号,"projectPath"
    Property sys;
    QMap<QString,Property> pluginInfo;
    QMap<std::string,QLibrary*> pluginDlls;
    //Flow相关参数
    int step;//表示画连接线进行到第几步,0(未开始)->1(点击了第一个输出按钮后的移动阶段)
    Flow *flow;//临时的对象,用于鼠标期间移动
    Shell *startObj;
    CountingMap<std::string,int> instanceCount;
    int flowInIndex;
    QString selectedPlugin;
    QMap<QString,QVector<QString> > instanceNames;
    Workspace *workspace;
    QString cellOldValue;

private:
    void initTypeMap();
    void initSysConfig();
    void createDefaultSysConfig();
    void loadAllPlugins();
    void loadPlugin(QString fileName);
    void unloadPlugin(std::string pluginName);
    void pluginConfig();
    void arrangeToolBox();
    void toolBoxReactions();
    void showToolTreeContextMenu(QPoint pos);
    void initInteraction();
    void addPlugin(QString pluginName,QString instanceName,QPointF center);
    void handleBeginEndConnection(Shell *obj, bool inputButtons, int index, int type);
    QString generateUniqueName(QString pluginName);
    void displayWorkspace();
    void popUpMatShow(const cv::Mat &img);
    QString getMatInfo(cv::Mat img);
    void cellEntered(int row,int col);
    void cellChanged(int row,int col);
};

#endif // MAINWINDOW_H
