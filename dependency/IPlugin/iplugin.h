#ifndef IPLUGIN_H
#define IPLUGIN_H

#include "iplugin_global.h"
#include <Any.h>
#include <vector>
#include <string>
#include <reflex.h>
#include <QWidget>

/**\brief 监听插件信息的接口
*/
class IPLUGINSHARED_EXPORT IPluginListener
{
public:
    /**\brief 由插件类向监听者(一般也是输入提供者)请求输入时调用
    */
    virtual void syncInputs()=0;
    /**\brief 设置运行处理进度,只由子类的run函数调用,用于刷新插件过程执行进度.不要覆盖
    */
    virtual void syncProgress(int state)=0;
    /**\brief 更新输出参数，在run函数中调用
     * \param[in] outVars输出参数
     * \param[in] changedItem给出哪些输出项数据发生了变化,以通知外界执行相应的响应;changedItem中的数只有在0~n-1之间才合法,指定
    */
    virtual void syncOutputs(const std::vector<Any>& outVars,const std::vector<int>& changedItem)=0;
};

/**\brief插件基类
 * \用法：自定义插件时继承此类，同时注册反射信息
 * \自定义插件实现函数:
 * \必须实现——getInputCount,getInputTypes,getOutputCount,getOutputTypes,run,cleanGarbage,openParameterWin
 * \可选实现(建议实现)——getDoc,getInputInfo,getOutputInfo,saveState,restoreState析构函数
 * \自定义插件基本要求——添加Reflex与IPlugin外部库以及Any.h头文件
*/
class IPLUGINSHARED_EXPORT IPlugin:public ReflexBase
{
private:
    std::vector<Any> m_outputs;
    int progress;//-1表示不在运行状态，0-100表示当前运行进度
    std::vector<IPluginListener*> listeners;

public:
    IPlugin();
    /**\brief 增加插件监听器
    */
    void addPluginListener(IPluginListener *listener);
    /**\brief 向listener请求输入参数以运行(具体运不运行取决于listener,因为输入参数不一定准备就绪)
    */
    void requestInputs();
    /**\brief 设置输入参数,参数数目必须与要求的输入参数对应，否则返回false
    */
    bool setInputArgs(std::vector<Any> inputs);
    /**\brief connectWorkspace连接工作空间
     */
    void connectWorkspace(std::map<std::string,Any> *workspace);
    /**\brief 判断是否插件的二级widget是内嵌式
    */
    bool widgetIsEmbeded();
    /**\brief 判断是否需要检查输入参数有效性(即输入参数是否有值——Any的指针不为NULL)
    */
    bool inputsValidityCheckRequired();
    /**\brief 获取输入参数个数
    */
    virtual int getInputCount()=0;
    /**\brief 获取输入参数类型
    */
    virtual std::vector<std::string> getInputTypes()=0;
    /**\brief 获取输出参数个数
    */
    virtual int getOutputCount()=0;
    /**\brief 获取输出参数类型
    */
    virtual std::vector<std::string> getOutputTypes()=0;
    /**\brief 插件核心功能实现函数,必须实现
    */
    virtual void run()=0;
    /**\brief 清理内存垃圾;因为每一次run运行完了都需要清理上一次的输出参数,输出参数究竟有哪些以及什么类型都只有在定义插件时才已知所以该函数必须实现以免运行垃圾堆积
     * \param[in] targets指定要清除的输出变量,有时候输出参数虽然变了,但是其地址没变,所以不能清除;否则把新的数据给清了
    */
    virtual void cleanGarbage(std::vector<Any> &outputVars,const std::vector<int> targets)=0;
    /**\brief 获取二级界面,可供主界面作为一个子控件插入,也可作为弹出窗口
     * \note:embededWidget参数决定是否为内嵌控件,默认为false,即默认为弹出窗口
    */
    virtual QWidget *getWidget();
    /**\brief 保存插件状态,返回一个状态文件的文件名;该文件怎么解析由restoreState实现,所以这两个函数必须成对定义
     * \note:默认的为返回空字符串,不能进行保存与恢复,因为具体的插件有哪些状态量并不知道需要由插件自身实现保存恢复状态
    */
    virtual std::string saveState();
    /**\brief 恢复插件状态,返回是否恢复成功
    */
    virtual bool restoreState(std::string stateFile);
    /**\brief 获取插件使用文档
    */
    virtual std::string getDoc();
    /**\brief 获取插件输入参数信息
    */
    virtual std::vector<std::string> getInputInfo();
    /**\brief 获取所有输出参数信息
    */
    virtual std::vector<std::string> getOutputInfo();
    /**\brief 析构清理操作
    */
    virtual ~IPlugin();

protected:
    std::vector<Any> m_inputs;
    std::map<std::string,Any> *workspace;
    bool embededWidget;
    bool inputsValidityRequired;
    /**\brief 子类使用该方法更新run执行进度
    */
    void setProgress(int state);
    /**\brief 子类run结束后使用该方法更新输出参数
    */
    void setOutputs(const std::vector<Any>& outputs,const std::vector<int> changedItem);
};

#endif // IPLUGIN_H
