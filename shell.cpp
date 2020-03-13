#include "shell.h"
#include "ui_shell.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <iostream>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <typenamedisplayer.h>
#include <typedatapeeker.h>

Shell::Shell(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Shell)
{
    ui->setupUi(this);
    this->syncProgress(-1);
    this->mouseHold=false;
    worker=NULL;
}

void Shell::init(QString pluginName, QString instanceName)
{
    this->workspace=NULL;
    this->pluginName=pluginName;
    this->instanceName=instanceName;
    core=(IPlugin*)Factory::CreateObject(pluginName.toStdString());
    //监听插件的变化
    core->addPluginListener(this);
    initPluginUi();
    if(core->getInputCount()==0){
        this->startProcess();//不需要输入参数的话直接就可以开始运行了
    }
    this->inFlows=QVector<Flow*>(core->getInputCount(),NULL);
    this->outFlows=QVector<QVector<Flow*> >(core->getOutputCount(),QVector<Flow*>());
    this->inputStateReady=QVector<bool>(core->getInputCount(),false);
    //右键菜单
    connect(this,&QWidget::customContextMenuRequested,this,[=](const QPoint &pos){
        this->showContextMenu(pos);
    });
}

void Shell::connectWorkspace(Workspace *work)
{
    this->workspace=work;
    if(core){
        core->connectWorkspace(this->workspace->getWorkspace());
        connect(workspace,&Workspace::recordChanged,this,[=](){
            this->core->connectWorkspace(this->workspace->getWorkspace());
        });
    }
//    connect(this,&Shell::myOutputChanged,work,&Workspace::setRecord);
    //初始化输出数据持有器
    std::vector<Any> outs_temp(core->getOutputCount(),Any());
    std::vector<bool> changed_temp(core->getOutputCount(),true);
    for(int i=0;i<outs_temp.size();++i){
        if(this->outputs.size()>i&&!this->outputs[i].isNull()){
            outs_temp[i].setData(this->outputs[i]);
        }
        this->workspace->setRecord(this,this->pluginName,this->instanceName,i,outs_temp[i]);
    }
}

QPointF Shell::nodePos(bool isInput, int index)
{
    int x0=this->geometry().left();
    int y0=this->geometry().top();
    int w=this->geometry().width();
    int h=this->geometry().height();
    float x=x0;
    float y=y0;
    if(isInput){
        float unit=(float)h/core->getInputCount();
        y+=index*unit+(float)unit/2;
    }
    else{
        float unit=(float)h/core->getOutputCount();
        y+=index*unit+(float)unit/2;
        x+=w;
    }
    return QPointF(x,y);
}

Shell::~Shell()
{
    if(this->workspace){
        //为了反之接下来一句又返回信号给this,给它disconnect以下,反正this已经开始析构,没必要接收任何信号了
        disconnect(this->workspace,0,this,0);
        this->workspace->deleteRecordsOf(this);
    }
    delete ui;
    if(this->outputs.size()>0){//Shell会提醒自己管理的IPlugin清理内存,所以IPlugin析构函数中无需清理
        std::vector<int> needClean;
        for(int i=0;i<this->outputs.size();++i){
            if(this->outputs[i].isNull()){
                needClean.push_back(0);
            }
            else{
                needClean.push_back(1);
            }
        }
        core->cleanGarbage(this->outputs,needClean);
    }
    delete core;
}

void Shell::syncInputs()
{
    if(core->getInputCount()==0){
        this->startProcess();
    }
    else{
        this->updateInputArgs(0);//随便发出一个参数更新信号使其执行
    }
}

void Shell::syncProgress(int state)
{
    if(state==-1){
        emit progressVisibilityChanged(false);
    }
    if(state>=0&&state<=100){
        emit progressVisibilityChanged(true);
        emit progressChanged(state);
    }
}

void Shell::syncOutputs(const std::vector<Any> &outVars, const std::vector<int> &changedItem)
{
    //同步输出到Flow
    outputs.clear();
    for(int i=0;i<outVars.size();++i){
        outputs.push_back(Any().setData(outVars[i]));
        if(changedItem[i]){
            for(Flow* f:this->outFlows[i]){
                f->setData(outVars[i]);
            }
            //同步到workspace
            if(this->workspace){
                this->workspace->setRecord(this,pluginName,this->instanceName,i,Any().setData(outVars[i]));
            }
//            emit myOutputChanged(this,this->pluginName,this->instanceName,i,outVars[i]);
        }
    }
}

void Shell::addOutFlow(Flow *flow, int index)
{
    outFlows[index].push_back(flow);
    connect(flow,&Flow::destroyed,this,[=](QObject *obj){//输出流删除时删除对应Shell中保存的指针
        Flow *temp=(Flow*)obj;
        auto it=std::find(outFlows[index].begin(),outFlows[index].end(),temp);
        if(outFlows[index].end()!=it){
            outFlows[index].erase(it);
        }
    });
    if(outputs.size()>index&&!outputs[index].isNull()){
        flow->setData(outputs[index]);
    }
}

bool Shell::addInFlow(Flow *flow, int index)
{
    if(index>=core->getInputCount())return false;
    if(this->inFlows.at(index)==NULL){
        this->inFlows[index]=flow;
        connect(flow,&Flow::dataChanged,this,[=](Flow *obj){
            this->updateInputArgs(index);
        });
        connect(flow,&Flow::destroyed,this,[=](QObject *obj){//输入流删除时删除输入参数列表中指针
            inFlows[index]=NULL;
            inputStateReady[index]=false;
        });
//        if(core->getInputTypes().at(index)=="null"){
//            //如果某个输入流对应的输入参数类型为“null",即接受任何类型,则有必要更新下输入参数//不需要,因为flow是先连接输入再连接输出,连接输出的时候数据自动就传过来了
//            this->updateInputArgs(index);
//        }
        return true;
    }
    else{
        return false;
    }
}

std::vector<std::string> Shell::getInputTypes()
{
    return core->getInputTypes();
}

std::vector<std::string> Shell::getOutputTypes()
{
    return core->getOutputTypes();
}

QString Shell::getPluginName()
{
    return this->pluginName;
}

QString Shell::getInstanceName()
{
    return this->instanceName;
}

void Shell::removeFlowsAndDelete()
{
    QVector<Flow*> inFs;
    for(auto f:this->inFlows){
        inFs.push_back(f);
    }
    for(int i=0;i<inFs.size();++i){
        if(inFs[i]!=NULL){
            delete inFs[i];
        }
    }
    QVector<QVector<Flow*> >outFs(this->outFlows.size(),QVector<Flow*>());
    for(int i=0;i<outFs.size();++i){
        for(auto f:this->outFlows[i]){
            outFs[i].push_back(f);
        }
    }
    for(int i=0;i<outFs.size();++i){
        for(int j=0;j<outFs[i].size();++j){
            if(outFs[i][j]!=NULL){
                delete outFs[i][j];
            }
        }
    }
    delete this;
}

void Shell::updateInputArgs(int index)
{
    bool allReady=true;
    if(core->inputsValidityCheckRequired()){
        this->inputStateReady[index]=this->inFlows[index]&&!this->inFlows[index]->dataIsNull();//只有相应的输入流连接了且相应的输入不为NULL才会设定相应的就绪状态为true
        allReady=this->inputArgsAllReady();
    }
    if(allReady){
        bool compatible=this->inputTypeCompatibilityCheck();
        if(compatible){
            std::vector<Any> inputs=std::vector<Any>(core->getInputCount(),Any());
            for(int i=0;i<inputs.size();++i){
                if(this->inFlows[i]){//inFlow[i]不为NULL则把相应的input设为其数据,否则保留为无数据的Any
                    inputs[i].setData(this->inFlows.at(i)->getData());
                }
            }
            core->setInputArgs(inputs);
            this->startProcess();
        }
    }
}

void Shell::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(!core->widgetIsEmbeded()&&core->getWidget()){
        dialog.raise();
        dialog.show();
    }
}

void Shell::mousePressEvent(QMouseEvent *event)
{
    this->setFocus();
    this->mouseHold=true;
    dragStart=event->windowPos();
}

void Shell::mouseMoveEvent(QMouseEvent *event)
{
    if(this->mouseHold){
        QPointF shift=event->windowPos()-dragStart;
        QPointF topLeftCorner=this->geometry().topLeft()+shift;
        float x=0>topLeftCorner.x()?0:topLeftCorner.x();
        x=x<this->parentWidget()->geometry().width()-this->geometry().width()?x:this->parentWidget()->geometry().width()-this->geometry().width();
        float y=0>topLeftCorner.y()?0:topLeftCorner.y();
        y=y<this->parentWidget()->geometry().height()-this->geometry().height()?y:this->parentWidget()->geometry().height()-this->geometry().height();
        topLeftCorner.setX(x);
        topLeftCorner.setY(y);
        this->setGeometry(topLeftCorner.x(),topLeftCorner.y(),this->size().width(),this->size().height());
        dragStart=event->windowPos();
        this->dragFlowsAlong();
    }
}

void Shell::mouseReleaseEvent(QMouseEvent *event)
{
    this->mouseHold=false;
}

void Shell::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Delete){
        emit requestSelfDestroy(this);
    }
}

void Shell::initPluginUi()
{
    //设置插件提示文本
    if(core->getDoc()!=""){
        this->setToolTip(QString::fromStdString(core->getDoc()));
    }
    //初始化插件外观
    QVBoxLayout *vb1=new QVBoxLayout();
    ui->leftWidget->setLayout(vb1);
    for(int i=0;i<core->getInputCount();++i){
        ParameterButton *pushButton=new ParameterButton();
        pushButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        QString displayText="["+this->typeNameForDisplay(core->getInputTypes()[i])+"]";
        std::vector<std::string> info=core->getInputInfo();
        if(info.size()>0){
            displayText+="\n"+QString::fromStdString(info.at(i));
        }
        pushButton->setToolTip(displayText);
        connect(pushButton,&QPushButton::clicked,this,[=](bool){this->inputClicked(i);});
        connect(pushButton,&ParameterButton::mouseEntered,this,[=](){this->inputEntered(i);});
        connect(pushButton,&ParameterButton::mouseLeft,this,[=](){this->inputLeft(i);});
        vb1->addWidget(pushButton);
        vb1->setContentsMargins(0,0,0,0);
        vb1->setSpacing(0);
        vb1->setStretchFactor(pushButton,1);
    }
    vb1->setContentsMargins(0,0,0,0);
    QVBoxLayout *vb2=new QVBoxLayout();
    ui->rightWidget->setLayout(vb2);
    for(int i=0;i<core->getOutputCount();++i){
        ParameterButton *pushButton=new ParameterButton();
        pushButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
        QString displayText="["+this->typeNameForDisplay(core->getOutputTypes()[i])+"]";
        std::vector<std::string> info=core->getOutputInfo();
        if(info.size()>0){
            displayText+="\n"+QString::fromStdString(info.at(i));
        }
        pushButton->setToolTip(displayText);
        connect(pushButton,&QPushButton::clicked,this,[=](bool){this->outputClicked(i);});
        connect(pushButton,&ParameterButton::mouseEntered,this,[=](){this->outputEntered(i);});
        connect(pushButton,&ParameterButton::mouseLeft,this,[=](){this->outputLeft(i);});
        vb2->addWidget(pushButton);
        vb2->setContentsMargins(0,0,0,0);
        vb2->setSpacing(0);
        vb2->setStretchFactor(pushButton,1);
    }
    vb2->setContentsMargins(0,0,0,0);
    //设置中间部分
    QWidget *mainWidget=core->getWidget();
    if(!core->widgetIsEmbeded()){
        ui->titleLabel->setText(this->pluginName);
        QLabel *centralLabel=new QLabel(instanceName);
        ui->centralFrame->layout()->addWidget(centralLabel);
        centralLabel->setAlignment(Qt::AlignCenter);
        if(mainWidget){
            dialog.setModal(false);
            QVBoxLayout *layout=new QVBoxLayout();
            dialog.setLayout(layout);
            layout->addWidget(mainWidget);
            dialog.resize(mainWidget->width(),mainWidget->height());
            dialog.setWindowTitle(tr("Parameters Dialog:")+this->pluginName+this->instanceName);
        }
    }
    else{
        ui->titleLabel->setText(this->pluginName+instanceName);
        if(mainWidget){
            ui->centralFrame->layout()->addWidget(mainWidget);
            int *left=new int();
            int *right=new int();
            int *top=new int();
            int *bottom=new int();
            ui->centralFrame->layout()->getContentsMargins(left,top,right,bottom);
            ui->centralFrame->resize(mainWidget->width()+*left+*right,mainWidget->height()+*top+*bottom);
            this->setMinimumHeight(ui->titleFrame->height()+ui->centralFrame->height());
            this->setMinimumWidth(ui->centralFrame->width()+ui->leftWidget->width()+ui->rightWidget->width());
        }
    }
    //设置信号连接
    ui->progressBar->setVisible(false);
    connect(this,&Shell::progressVisibilityChanged,ui->progressBar,&QProgressBar::setVisible);
    connect(this,&Shell::progressChanged,ui->progressBar,&QProgressBar::setValue);
    //接下来是根据插件配置信息设置插件外观

}

void Shell::inputClicked(int index)
{
    emit mouseOperation(this,true,index,2);
}

void Shell::outputClicked(int index)
{
    emit mouseOperation(this,false,index,2);
}

void Shell::inputEntered(int index)
{
    emit mouseOperation(this,true,index,0);
}

void Shell::inputLeft(int index)
{
    emit mouseOperation(this,true,index,1);
}

void Shell::outputEntered(int index)
{
    emit mouseOperation(this,false,index,0);
}

void Shell::outputLeft(int index)
{
    emit mouseOperation(this,false,index,1);
}

QString Shell::typeNameForDisplay(std::string name)
{
    //一些太长的类型名称在这里给出简略等效替代
    return TypeNameDisplayer::toDisplay(QString::fromStdString(name));
}

void Shell::startProcess()
{
//    if(worker&&worker->isRunning()){
//        worker->terminate();//重启新的处理最好先杀死之前的线程，以防数据访问冲突
//    }//这里不能把先前的线程杀死,会导致崩溃,可能因为每一次调用startProcess是异步的,先前生成的线程可能还没有启动
    worker=new PluginWorker(core);
    connect(worker,&PluginWorker::exceptionOccurred,this,[=](QString info){
        QString message="\nan exception occurred while pluginning is running\n\nPlugin name:"+this->pluginName+"\nInstance name:"+this->instanceName;
        message+="\n\nThe exception information is:\n"+info;
        QMessageBox::warning(0, QString(tr("plugin run time exception")),message,QMessageBox::Ok);
    });
    connect(worker,&PluginWorker::exceptionOccurred,ui->progressBar,[=](QString info){
        emit progressVisibilityChanged(false);
    });
    worker->start();
}

void Shell::showContextMenu(const QPoint &pos)
{
    //右键菜单
    QMenu menu;
    QAction runAction;
    QAction stopAction;
    QAction deleteAction;
    runAction.setText(tr("run"));
    stopAction.setText(tr("terminate"));
    deleteAction.setText(tr("delete"));
    connect(&runAction,&QAction::triggered,this,[=](bool){
        if(core->inputsValidityCheckRequired()&&!this->inputArgsAllReady()){//需要验证输入参数有效性且并不是所有参数有效时,才弹出警告
            QMessageBox::warning(this,tr("Parameter error"),tr("Input parameters not ready!\nplease check that all input sockets have been connected and all flow in data is not null!"),QMessageBox::Abort);
        }
        else{
            this->syncInputs();
        }
    });
    connect(&stopAction,&QAction::triggered,this,[=](bool){
        if(this->worker&&this->worker->isRunning()){
            this->worker->terminate();
            ui->progressBar->setVisible(false);
        }
    });
    connect(&deleteAction,&QAction::triggered,this,[=](bool checked){
        if(this->ui->progressBar->isVisible()){
            int answer=QMessageBox::question(this,tr("plugin is running!"),tr("the current plugin is running,do you want to terminate it and delete it?"),QMessageBox::Yes,QMessageBox::No);
            if(answer==QMessageBox::Yes){
                if(this->worker->isRunning()){
                    this->worker->terminate();
                }
                this->removeFlowsAndDelete();
            }
        }
        else{
            this->removeFlowsAndDelete();
        }
    });
    menu.addAction(&runAction);
    menu.addAction(&stopAction);
    menu.addSeparator();
    menu.addAction(&deleteAction);
    menu.exec(QCursor::pos());
}

bool Shell::inputArgsAllReady()
{
    if(core->getInputCount()==0)return true;
    bool allReady=true;
    for(auto r:this->inputStateReady){
        allReady=allReady&&r;
    }
    return allReady;
}

bool Shell::inputTypeCompatibilityCheck()
{
    bool allSame=true;
    std::vector<std::string> flowInTypes;
    for(int i=0;i<this->inFlows.size();++i){
        if(!inFlows[i]){//如果为NULL
            flowInTypes.push_back("null");
        }
        else{
            flowInTypes.push_back(this->inFlows.at(i)->peekType());
        }
    }
    std::vector<std::string> realTypes=core->getInputTypes();
    for(int i=0;i<flowInTypes.size();++i){
        if(flowInTypes[i]!=realTypes[i]&&realTypes[i]!="null"){//这里实际上只要插件的输入端口类型是"null"就表示接收任何类型
            allSame=false;
            inFlows[i]->setLineColor(Qt::red);//异常连接类型不符
            inFlows[i]->freezeFlow(true);
        }
    }
    return allSame;
}

void Shell::dragFlowsAlong()
{
    for(int i=0;i<inFlows.size();++i){
        QPointF p=this->nodePos(true,i);
        if(inFlows[i]!=NULL){
            inFlows[i]->setEndNode(p);
        }
    }
    for(int i=0;i<outFlows.size();++i){
        QPointF p=this->nodePos(false,i);
        for(int j=0;j<outFlows[i].size();++j){
            outFlows[i][j]->setStartNode(p);
        }
    }
}

void ParameterButton::enterEvent(QEvent *)
{
    emit mouseEntered();
}

void ParameterButton::leaveEvent(QEvent *)
{
    emit mouseLeft();
}

void Shell::on_progressBar_valueChanged(int value)
{
    ui->progressBar->setToolTip(QString(value)+"%");
}

PluginWorker::PluginWorker(IPlugin *plugin)
{
    this->plugin=plugin;
}

void PluginWorker::run()
{
    try{
        this->plugin->run();
    }
    catch(std::exception e){
        QString info="std::exception occurred while plugin is running!\n"+
                QString::fromStdString(std::string(e.what()));
        emit exceptionOccurred(info);
        this->terminate();
    }
#ifdef QT_NO_DEBUG
    //release版本下不允许任何异常导致程序崩溃，出现该异常时在debug下调试并确定异常类型然后在上面添加相应的捕捉处理
    catch(...){
        emit std::runtime_error("non std::exception occurred while plugin running\n! Some unknown error occurred!");
    }
#endif
}

void Workspace::setRecord(Shell *target, QString pluginName, QString instanceName, int index, Any data)
{
    int pos=0;
    for(;pos<plugins.size();++pos){
        if(this->plugins[pos]==target&&this->indices[pos]==index){//同一个插件的同一个输出
            break;
        }
    }
    if(pos==plugins.size()){//添加
        //默认每一个插件的类型、名称不全一样,每一个输出只有一个工作空间记录
        this->varNames.append(pluginName+instanceName+"_output"+QString::number(index));
        this->plugins.append(target);
        this->pluginNames.append(pluginName);
        this->instanceNames.append(instanceName);
        this->indices.append(index);
        this->data.append(data);
    }
    else{//修改
        this->pluginNames[pos]=pluginName;
        this->instanceNames[pos]=instanceName;
        this->data[pos].setData(data);
    }
    emit recordChanged();
}

Workspace::Workspace()
{
    this->varNames.resize(0);
    this->plugins.resize(0);
    this->pluginNames.resize(0);
    this->instanceNames.resize(0);
    this->indices.resize(0);
    this->data.resize(0);
}

void Workspace::renameOutput(QString oldName, QString newName)
{
    int pos=this->varNames.indexOf(oldName);
    if(pos!=-1){//oldName存在
        if(this->varNames.indexOf(newName)==-1){//newName不存在
            this->varNames[pos]=newName;
            emit recordChanged();
        }
    }
}

void Workspace::deleteRecordsOf(Shell *target)
{
    int pos=this->plugins.indexOf(target);
    while(pos!=-1){
        this->varNames.remove(pos);
        this->plugins.remove(pos);
        this->pluginNames.remove(pos);
        this->instanceNames.remove(pos);
        this->indices.remove(pos);
        this->data.remove(pos);
        pos=this->plugins.indexOf(target);
    }
    emit recordChanged();
}

QVector<QVector<QString> > Workspace::getAllRecords()
{
    QVector<QVector<QString> > result;
    for(int i=0;i<this->varNames.size();++i){
        result.push_back(QVector<QString>());
        result[i].push_back(this->varNames[i]);//变量名
        result[i].push_back(this->pluginNames[i]);//所属插件
        result[i].push_back(this->instanceNames[i]);//所属实例
        result[i].push_back(QString::number(this->indices[i]));//输出参数序号
        result[i].push_back(TypeNameDisplayer::toDisplay(QString::fromStdString(this->data[i].getType())));//数据类型
        result[i].push_back(QString::number(long(this->data[i].getAddress()),16));//数据地址
        result[i].push_back(TypeDataPeeker::peek(this->data[i]));
    }
    return result;
}

std::map<std::string, Any> *Workspace::getWorkspace()
{
    std::map<std::string,Any> *result=new std::map<std::string,Any>();
    for(int i=0;i<this->varNames.size();++i){
        (*result)[this->varNames[i].toStdString()]=Any().setData(this->data[i]);
    }
    return result;
}

Any Workspace::getData(int row)
{
    return Any().setData(this->data.at(row));
}
