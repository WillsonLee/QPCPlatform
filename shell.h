#ifndef SHELL_H
#define SHELL_H

#include <QWidget>
#include <QVector>
#include <reflex.h>
#include <iplugin.h>
#include <QMouseEvent>
#include <QPushButton>
#include <QPointF>
#include <flow.h>
#include <Any.h>
#include <QThread>
#include <QDialog>

class Shell;
/**
 * @brief The ParameterButton class 插件输入输出参数按钮
 */
class ParameterButton:public QPushButton
{
    Q_OBJECT

protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);

signals:
    void mouseEntered();
    void mouseLeft();
};
/**
 * @brief The PluginWorker class 插件运行内部过程的代理线程(以实现每个插件的执行过程都是独立互不影响的)
 */
class PluginWorker:public QThread
{
    Q_OBJECT

public:
    PluginWorker(IPlugin *plugin);

signals:
    void exceptionOccurred(QString info);

    // QThread interface
protected:
    void run();
private:
    IPlugin *plugin;
};
/**
 * @brief The Workspace class 工作空间类,保存所有输出参数信息,作为主界面输出参数表格显示的数据源
 */
class Workspace:public QObject
{
    Q_OBJECT

public:
    Workspace();
    void renameOutput(QString oldName,QString newName);//由worksapceDock使用,管理输出变量名
    void deleteRecordsOf(Shell *target);
    QVector<QVector<QString> > getAllRecords();
    std::map<std::string,Any> *getWorkspace();
    Any getData(int row);
public slots:
    void setRecord(Shell *target, QString pluginName, QString instanceName, int index, Any data);
signals:
    void recordChanged();
private:
    //以下数组必须始终保持大小一致
    QVector<QString> varNames;
    QVector<Shell*> plugins;
    QVector<QString> pluginNames;
    QVector<QString> instanceNames;
    QVector<int> indices;
    QVector<Any> data;
};

namespace Ui {
class Shell;
}
/**
 * @brief The Shell class 插件外壳类,管理插件与外界的数据交互(输入数据的流入,输出数据的流出)以及插件是否执行过程等;插件套上壳就可以以统一的方式与界面交互
 */
class Shell : public QWidget,public IPluginListener
{
    Q_OBJECT

public:
    explicit Shell(QWidget *parent = 0);
    void init(QString pluginName,QString instanceName);
    void connectWorkspace(Workspace *work);
    QPointF nodePos(bool isInput, int index);
    ~Shell();

private:
    Ui::Shell *ui;
    IPlugin *core;
    QDialog dialog;
    QString pluginName;
    QString instanceName;
    bool mouseHold;
    QPointF dragStart;
    QVector<Flow*> inFlows;
    QVector<QVector<Flow*> > outFlows;
    std::vector<Any> outputs;
    QVector<bool> inputStateReady;
    PluginWorker *worker;
    Workspace *workspace;

    // IPluginListener interface
public:
    void syncInputs();
    void syncProgress(int state);
    void syncOutputs(const std::vector<Any> &outVars, const std::vector<int> &changedItem);
    void addOutFlow(Flow *flow,int index);
    bool addInFlow(Flow *flow,int index);
    std::vector<std::string> getInputTypes();
    std::vector<std::string> getOutputTypes();
    QString getPluginName();
    QString getInstanceName();
    void removeFlowsAndDelete();
public slots:
    void updateInputArgs(int index);
    // 事件监听
protected:
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
signals:
    void mouseOperation(Shell *obj,bool inputButtons,int index,int type);
    void myOutputChanged(Shell *myId, QString myType, QString myName, int index,Any changedData);
    void progressChanged(int state);
    void progressVisibilityChanged(bool visible);
    void requestSelfDestroy(Shell *obj);
private slots:
    void on_progressBar_valueChanged(int value);
    // 私有函数(辅助)
private:
    void initPluginUi();
    void inputClicked(int index);
    void outputClicked(int index);
    void inputEntered(int index);
    void inputLeft(int index);
    void outputEntered(int index);
    void outputLeft(int index);
    QString typeNameForDisplay(std::string name);
    void startProcess();
    void showContextMenu(const QPoint &pos);
    bool inputArgsAllReady();
    bool inputTypeCompatibilityCheck();
    void dragFlowsAlong();//插件位置或大小变化时拖动输入输出数据流一起改变
};

#endif // SHELL_H
