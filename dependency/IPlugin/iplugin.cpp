#include "iplugin.h"
#include <iostream>

IPlugin::IPlugin()
{
    progress=-1;
    embededWidget=false;
    inputsValidityRequired=true;
}

void IPlugin::addPluginListener(IPluginListener *listener)
{
    if(listeners.end()==find(listeners.begin(),listeners.end(),listener)){
        listeners.push_back(listener);
    }
}

void IPlugin::requestInputs()
{
    for(IPluginListener* listener:listeners){
        listener->syncInputs();
    }
}

bool IPlugin::setInputArgs(std::vector<Any> inputs)
{
    m_inputs.clear();
    for(int i=0;i<inputs.size();++i){
        m_inputs.push_back(Any().setData(inputs[i]));
    }
    return true;
}

void IPlugin::connectWorkspace(std::map<std::string, Any> *workspace)
{
    this->workspace=workspace;
}

bool IPlugin::widgetIsEmbeded()
{
    return this->embededWidget;
}

bool IPlugin::inputsValidityCheckRequired()
{
    return this->inputsValidityRequired;
}

QWidget *IPlugin::getWidget()
{
    return NULL;
}

std::string IPlugin::saveState()
{
    return "";
}

bool IPlugin::restoreState(std::string stateFile)
{
    return false;
}

std::string IPlugin::getDoc()
{
    return std::string("documentation not defined");
}

std::vector<std::string> IPlugin::getInputInfo()
{
    return std::vector<std::string>();
}

std::vector<std::string> IPlugin::getOutputInfo()
{
    return std::vector<std::string>();
}

IPlugin::~IPlugin()
{

}

void IPlugin::setProgress(int state)
{
    if(progress!=state&&state>=-1&&state<=100){
        progress=state;
        for(IPluginListener* listener:listeners){
            listener->syncProgress(state);
        }
    }
}

void IPlugin::setOutputs(const std::vector<Any> &outputs, const std::vector<int> changedItem)
{
    std::vector<int> toClean;
    if(this->m_outputs.size()==0){
        for(int i=0;i<this->getOutputCount();++i){
            this->m_outputs.push_back(Any());//初始输出参数个数
        }
    }
    for(int i=0;i<m_outputs.size();++i){
        if(m_outputs[i].isSameAs(outputs[i])||m_outputs[i].isNull()){
            toClean.push_back(0);
        }
        else{
            toClean.push_back(1);
        }
    }
    cleanGarbage(this->m_outputs,toClean);//清除上一次输出参数内存
    this->m_outputs.clear();
    for(const Any &var:outputs){
        m_outputs.push_back(var);
    }
    for(IPluginListener* listener:listeners){
        listener->syncOutputs(m_outputs,changedItem);
    }
    setProgress(-1);//这里确保执行该函数后整个过程进度条结束,以免写插件的时候忘了
}
