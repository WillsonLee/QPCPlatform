#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QDomDocument>
#include <QDomElement>
#include <QDomComment>
#include <QDomNode>
#include <QDomText>
#include <QDomNodeList>
#include <QTime>
#include <QTextStream>
#include <QIODevice>
#include <QBoxLayout>
#include <QPainter>
#include <QPen>
#include <QKeyEvent>
#include <QLineEdit>
#include <QProcess>
#include <QFileDialog>
#include <intropagewidget.h>
#include <proppagewidget.h>
#include <QLabel>
#include <QMessageBox>
#include <QDateTime>
#include <QDesktopWidget>
#include <typenamedisplayer.h>
#include <qtpclviewer.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置根目录，安装程序后也是从QPCPlatform目录启动
    sys.setProperty("rootPath",QDir::currentPath());
    //初始化类型显示名称映射表
    initTypeMap();
    //加载系统配置文件
    initSysConfig();
    //加载插件
    loadAllPlugins();
    //插件属性初始化
    this->pluginConfig();
    //布置工具箱
    this->arrangeToolBox();
    //设置工具箱响应
    this->toolBoxReactions();
    //初始化界面交互性(指添加插件与连接插件等)参数
    initInteraction();
    //初始化工作空间
    this->workspace=new Workspace();
    this->displayWorkspace();
    connect(this->workspace,&Workspace::recordChanged,this,&MainWindow::displayWorkspace);
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseMove&&watched==ui->centralWidget){
        QMouseEvent *e=(QMouseEvent*)event;
        QPoint pos=e->pos();
        ui->statusBar->showMessage(QString("(%1,%2)").arg(pos.x()).arg(pos.y()));
        if(step==1){//连接插件的第二个端点步骤(移动)
            flow->setEndNode(pos);
            this->update();
        }
    }
    if(event->type()==QEvent::MouseButtonPress){
        if(step==-1){//放置插件步骤
            this->addPlugin(selectedPlugin,this->generateUniqueName(selectedPlugin),ui->centralWidget->mapFromGlobal(QCursor::pos()));
            QCursor cursor;
            cursor.setShape(Qt::ArrowCursor);
            setCursor(cursor);
            step=0;
        }
//        qDebug()<<"fuck you"<<endl;
        if(step==1){
//            qDebug()<<"mouse pressed and step==1"<<endl;
            if(flow!=NULL){
                delete flow;
                flow=NULL;
            }
            step=0;
        }
    }
//    qDebug()<<"event occured,object is centralWidget?"<<(watched==ui->centralWidget)<<endl;
    if(event->type()==QEvent::KeyPress){
//        qDebug()<<"key pressed"<<endl;
        if(step==1){
//            qDebug()<<"step==1"<<endl;
            QKeyEvent *ke=(QKeyEvent*)event;
            if(ke->key()==Qt::Key_Escape){
//                qDebug()<<"key pressed is Esc"<<endl;
                if(flow!=NULL){
                    delete flow;
                    flow=NULL;
                }
                step=0;
            }
        }
        if(step==-1){
            QKeyEvent *ke=(QKeyEvent*)event;
            if(ke->key()==Qt::Key_Escape){//取消添加插件命令
//                qDebug()<<"step==-1 and key== Esc"<<endl;
                QCursor cursor;
                cursor.setShape(Qt::ArrowCursor);
                setCursor(cursor);
                step=0;
            }
        }
    }
    return QWidget::eventFilter(watched,event);
}

MainWindow::~MainWindow()
{
    //必须在这里解除workspace与this的连接,否则之后table delete了workspace还给this发信号让其更改table
    //2019.9.20注:这里之所以必须断开workspace与this的连接是因为,delete ui时主界面的TableWidget先死了,
    //然后是各个Shell,各个Shell死的时候回通知workspace更改去掉自己的输出;workspace更改后会发出recordChanged信号
    //而此时主界面this并没有死,所以会接收该信号;但是主界面处理该信号的槽操作了TableWidget,这东西已经不在了,所以出错
    disconnect(this->workspace,0,this,0);
    delete ui;
    if(all_plugins){
        delete all_plugins;
    }
}

void MainWindow::initTypeMap()
{
    TypeNameDisplayer::initMaps();
    QFile mapFile(sys.getProperty("rootPath")+"/configure/types.xml");
    if(!mapFile.open(QFile::ReadOnly)){
        return;
    }
    QDomDocument doc;
    doc.setContent(&mapFile);
    mapFile.close();
    QDomElement root=doc.firstChildElement("types");
    QDomNodeList types=root.elementsByTagName("type");
    for(int i=0;i<types.count();++i){
        QDomElement type=types.at(i).firstChildElement("typeName");
        QDomElement display=types.at(i).firstChildElement("displayName");
        TypeNameDisplayer::addTypeStrMap(type.text(),display.text());
    }
}

void MainWindow::initSysConfig()
{
    if(!QFileInfo(sys.getProperty("rootPath")+"/configure/sys.xml").isFile()){
        createDefaultSysConfig();
        return;
    }
    QFile file(sys.getProperty("rootPath")+"/configure/sys.xml");
    file.open(QFile::ReadOnly);
    QDomDocument doc;
    doc.setContent(&file);
    file.close();
    //下面解析xml文档,只能解析定义过的部分
    QDomElement root=doc.firstChildElement("sys");
    QDomElement plugin_paths=root.firstChildElement("pluginPaths");
    QDomNodeList paths=plugin_paths.elementsByTagName("folder");
    sys.setProperty("pluginPathCount",QString::number(paths.count()));
    for(int i=0;i<paths.count();++i){
        sys.setProperty("folder"+i,paths.at(i).toElement().text());
    }
    QDomElement proPath=root.firstChildElement("projectPath");
    sys.setProperty("projectPath",QDir(proPath.text()).absolutePath());
}

void MainWindow::createDefaultSysConfig()
{
    QDomDocument doc;
    //下面是编辑xml文档
    QDomElement root=doc.createElement("sys");
    doc.appendChild(root);
    QDomElement plugin_paths=doc.createElement("pluginPaths");
    root.appendChild(plugin_paths);
    QDomElement folder=doc.createElement("folder");
    plugin_paths.appendChild(folder);
    QDomText f_path=doc.createTextNode(sys.getProperty("rootPath")+"/plugins");
    folder.appendChild(f_path);
    //
    QFile file(sys.getProperty("rootPath")+"/configure/sys.xml");
    if(!file.open(QFile::WriteOnly|QFile::Truncate|QFile::Text)){
        return;
    }
    QTextStream ts(&file);
    ts.setCodec("utf-8");
    doc.save(ts,4,QDomNode::EncodingFromTextStream);
    file.close();
}

void MainWindow::loadAllPlugins()
{
    QList<QString> paths;
    int count=sys.getProperty("pluginPathCount","0").toInt();
    for(int i=0;i<count;++i){
        paths.append(sys.getProperty("folder"+QString::number(i),sys.getProperty("rootPath")+"/plugins"));
    }
    for(QString path:paths){
        QDir dir(path);
        QStringList nameFilters;
#ifdef Q_OS_WIN32
        nameFilters<<"*.dll";
#endif
#ifdef Q_OS_LINUX
        nameFilters<<"*.so";
#endif
        QStringList files=dir.entryList(nameFilters,QDir::Files|QDir::Readable,QDir::Name);
        for(auto f:files){
            this->loadPlugin(path+"/"+f);
        }
    }
}

void MainWindow::loadPlugin(QString fileName)
{
    //加载名称为fileName的插件
    QLibrary *lib=new QLibrary(fileName);
    if(lib->load()){
        ui->statusBar->showMessage(QString("lib file named %1 loaded successfully!").arg(fileName));
        std::string added=Factory::getNewAddedClassName();
        if(!pluginDlls.contains(added)){//plugins already added can not be loaded again!
            pluginDlls[added]=lib;
        }
    }
    else{
        ui->statusBar->showMessage(QString("unable to load lib file:%1").arg(fileName));
    }
    delete lib;
}

void MainWindow::unloadPlugin(std::string pluginName)
{
    if(pluginDlls.contains(pluginName)){
        pluginDlls[pluginName]->unload();
        pluginDlls.remove(pluginName);
    }
    Factory::Unregister(pluginName);
}

void MainWindow::pluginConfig()
{
    //该函数主要更新所有插件名all_plugins以及更新所有插件对应的信息/属性pluginInfo
    if(this->pluginInfo.size()>0){
        this->pluginInfo.clear();
    }
    all_plugins=Factory::GetClassNames();
    for(auto name:*all_plugins){
        pluginInfo.insert(QString::fromStdString(name),Property());
    }
    QFile file(sys.getProperty("rootPath")+"/configure/plugins.xml");
    if(!file.open(QFile::ReadOnly)){
        return;
    }
    QDomDocument doc;
    doc.setContent(&file);
    file.close();
    //解析插件属性xml文档
    QDomElement root=doc.firstChildElement("plugins");
    QDomNodeList plugins=root.elementsByTagName("plugin");
    for(int i=0;i<plugins.count();++i){
        QDomElement node=plugins.at(i).toElement();
        if(node.attributes().contains("name")){//必须要包含name属性
            QString name=node.attribute("name");
            if(this->pluginInfo.contains(name)){//name属性的值必须是一个已定义的插件名称
                //分组信息
                Property &plugPro=this->pluginInfo[name];
                QString group=node.firstChildElement("group").text();
                plugPro.setProperty("group",group);
                //
            }
        }
    }
}

void MainWindow::arrangeToolBox()
{
    //清理
    ui->toolsTree->clear();
    //插件按组分配
    ui->toolsTree->setColumnCount(1);
    QList<QTreeWidgetItem*> items;
    QMap<QString,QVector<QString> >mapGroupName;
    for(auto name:*all_plugins){
        Property info=pluginInfo[QString::fromStdString(name)];
        QString groupName=info.getProperty("group","ungrouped");
        mapGroupName[groupName].append(QString::fromStdString(name));
    }
    //添加分组
    for(auto group:mapGroupName.keys()){
        items.append(new QTreeWidgetItem((QTreeWidget*)0,QStringList(QString(group))));
    }
    ui->toolsTree->insertTopLevelItems(0,items);
    //对每一个分组添加插件
    for(auto item:items){
        for(auto child:mapGroupName[item->text(0)]){
            QTreeWidgetItem *tool=new QTreeWidgetItem((QTreeWidget*)0,QStringList(QString(child)));
            item->addChild(tool);
        }
    }
    ui->toolsTree->expandAll();
}

void MainWindow::toolBoxReactions()
{
    //设置叶子节点响应函数
    connect(ui->toolsTree,&QTreeWidget::itemClicked,this,[=](QTreeWidgetItem *item,int column){
        if(item->childCount()==0){
            this->selectedPlugin=item->text(0);
            QCursor cursor;
            cursor.setShape(Qt::CrossCursor);
            setCursor(cursor);
            step=-1;
        }
    });
    //叶子节点右键菜单
    ui->toolsTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->toolsTree,&QTreeWidget::customContextMenuRequested,this,&MainWindow::showToolTreeContextMenu);
}

void MainWindow::showToolTreeContextMenu(QPoint pos)
{
    QTreeWidgetItem *current=ui->toolsTree->itemAt(pos);
    //仅没有子选项的叶子节点才能调出该右键菜单
    if(current&&current->childCount()==0){
        QMenu menu(ui->toolsTree);
        QAction unload(tr("unload"),ui->toolsTree);
        menu.addAction(&unload);
        connect(&unload,&QAction::triggered,[=](){
            std::string cur_plugin=current->text(0).toStdString();
            if(instanceCount.contains(cur_plugin)&&instanceCount[cur_plugin]>0){
                QMessageBox::warning(this,tr("unload library failed"),tr("the selected plugin can not be unloaded unless all instances of the plugin have been deleted!"),QMessageBox::Abort);
            }
            else{
                if(pluginDlls.contains(cur_plugin)){
                    pluginDlls[cur_plugin]->unload();
                    pluginDlls.remove(cur_plugin);
                    Factory::Unregister(cur_plugin);
                    ui->statusBar->showMessage("plugin "+QString::fromStdString(cur_plugin)+" has been unloaded!");
                    this->pluginConfig();
                    this->arrangeToolBox();
                }
            }
        });
        menu.exec(QCursor::pos());
    }
}

void MainWindow::initInteraction()
{
    ui->centralWidget->setMouseTracking(true);
    ui->centralWidget->installEventFilter(this);
    step=0;
}

void MainWindow::addPlugin(QString pluginName, QString instanceName, QPointF center)
{
    Shell *shell=new Shell(ui->centralWidget);
    shell->init(pluginName,instanceName);
    int w=100;
    int h=70;
    shell->setGeometry(QRect(center.x()-w/2,center.y()-h/2,w,h));
    connect(shell,&Shell::mouseOperation,this,&MainWindow::handleBeginEndConnection);
    shell->setVisible(true);
    shell->connectWorkspace(this->workspace);
    ui->centralWidget->update();
    connect(shell,&Shell::requestSelfDestroy,this,[=](Shell *obj){
        obj->removeFlowsAndDelete();
        //以下两步是必不可少的麻烦事,非得调整过centralWidget然后才update才有效
        ui->centralWidget->setVisible(false);
        this->update();
        ui->centralWidget->setVisible(true);
        this->update();
    });
    //更新插件实例计数
    std::string std_name=pluginName.toStdString();
    if(instanceCount.contains(std_name)){
        instanceCount[std_name]++;
    }
    else{
        instanceCount[std_name]=1;
    }
    //在主程序结束时析构MainWindow对象可能instanceCount先于shell销毁,所以该函数回调访问了已经不存在的instanceCount！
    connect(shell,&Shell::destroyed,&instanceCount,[=](){
        if(instanceCount.contains(std_name)){
            instanceCount[std_name]--;
        }
    });
}

void MainWindow::handleBeginEndConnection(Shell *obj, bool inputButtons, int index, int type)
{
    //处理连接过程中开始结束的动作
    if(step==0){//连接插件的第一个端点步骤
        if(!inputButtons&&type==2){
            flow=new Flow(ui->centralWidget);
            QList<QWidget*> allWidgets=ui->centralWidget->findChildren<QWidget*>();
            for(auto *w:allWidgets){//将flow置于底层
                if(flow!=w){
                    w->raise();
                }
            }
            flow->setStartNode(obj->nodePos(inputButtons,index));
            connect(flow,&Flow::mouseMoved,this,[=](QPointF pos){
                QPointF posInParent=pos-ui->centralWidget->mapToGlobal(QPoint(0,0));
                QMouseEvent *manualEvent=new QMouseEvent(
                            QEvent::MouseMove,posInParent,Qt::NoButton,Qt::NoButton,Qt::NoModifier);
                this->eventFilter(ui->centralWidget,manualEvent);
            });
            flow->setVisible(true);
            startObj=obj;
            flowInIndex=index;
            step=1;//进入下一步
        }
    }
    else if(step==1){//连接插件的第二个端点步骤(点击)
        if(obj!=startObj){//事件发生于不同的插件上
            if(inputButtons){
                flow->setEndNode(obj->nodePos(inputButtons,index));
                if(startObj->getOutputTypes()[flowInIndex]==obj->getInputTypes()[index]||
                        startObj->getOutputTypes()[flowInIndex]=="null"||
                        obj->getInputTypes()[index]=="null"){
                    //输出输入端口正确连接的情形为二者数据类型相同或者其中任一方数据类型为null
                    if(type==0){
                        ui->statusBar->showMessage(tr("click to connect"));
                    }
                    if(type==2){//在这里成功连接flow
                        if(obj->addInFlow(flow,index)){
                            startObj->addOutFlow(flow,flowInIndex);
                            flow->setLineColor(Qt::green);
                            flow->installEventFilter(this);
                        }
                        else{
                            ui->statusBar->showMessage(tr("input socket has been occupied!"));
                            delete flow;
                            flow=NULL;
                        }
                        step=0;
                    }
                }
                else{
                    ui->statusBar->showMessage(tr("output type and input type incompatible!"));
                    if(type==0){
                        flow->setLineColor(Qt::red);
                    }
                    if(type==1){
                        flow->setLineColor(Qt::blue);
                    }
                    if(type==2){
                        delete flow;
                        flow=NULL;
                        step=0;
                    }
                }
            }
            else{
                ui->statusBar->showMessage(tr("output cannot be connected to output!"));
            }
        }
        else{
            ui->statusBar->showMessage(tr("output and input of the same plugin cannot be connected!"));
        }
    }
    if(!inputButtons&&type==0&&ui->tableWidget->rowCount()>0){//鼠标进入参数按钮除了显示提示文本以外还要定位输出显示表中对应行
        for(int i=0;i<ui->tableWidget->rowCount();++i){
            bool sameSocket=ui->tableWidget->item(i,1)->text()==obj->getPluginName();
            sameSocket=sameSocket&&ui->tableWidget->item(i,2)->text()==obj->getInstanceName();
            sameSocket=sameSocket&&ui->tableWidget->item(i,3)->text().toDouble()==index;
            if(sameSocket){
                ui->tableWidget->selectRow(i);
                break;
            }
        }
    }
    this->update();
}

QString MainWindow::generateUniqueName(QString pluginName)
{
    int index=1;
    QString name="#"+QString::number(index);
    if(instanceNames.contains(pluginName)){
        while(instanceNames[pluginName].contains(name)){
            index++;
            name="#"+QString::number(index);
        }
    }
    this->instanceNames[pluginName].append(name);
    return name;
}

void MainWindow::displayWorkspace()
{
    QVector<QVector<QString> > table;
    if(this->workspace){
        table=this->workspace->getAllRecords();
    }
    ui->tableWidget->disconnect(this);
    ui->tableWidget->clear();
    //初始化表头
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderItem(0,new  QTableWidgetItem(tr("variable name")));
    ui->tableWidget->setHorizontalHeaderItem(1,new  QTableWidgetItem(tr("plugin name")));
    ui->tableWidget->setHorizontalHeaderItem(2,new  QTableWidgetItem(tr("instance name")));
    ui->tableWidget->setHorizontalHeaderItem(3,new  QTableWidgetItem(tr("index of output")));
    ui->tableWidget->setHorizontalHeaderItem(4,new  QTableWidgetItem(tr("data type")));
    ui->tableWidget->setHorizontalHeaderItem(5,new  QTableWidgetItem(tr("data address")));
    ui->tableWidget->setHorizontalHeaderItem(6,new  QTableWidgetItem(tr("data")));
    ui->tableWidget->setRowCount(table.size());
    //初始化表格内容
    for(int i=0;i<table.size();++i){
        for(int j=0;j<table[i].size();++j){
            QTableWidgetItem *item=new QTableWidgetItem(table[i][j]);
            ui->tableWidget->setItem(i,j,item);
            if(j){
                ui->tableWidget->item(i,j)->setFlags(ui->tableWidget->item(i,j)->flags()&~Qt::ItemIsEditable);//不可编辑
            }
            else{
                connect(ui->tableWidget,&QTableWidget::cellEntered,this,&MainWindow::cellEntered);
                connect(ui->tableWidget,&QTableWidget::cellChanged,this,&MainWindow::cellChanged);
            }
        }
    }
    //设置单元格双击回调
    connect(ui->tableWidget,&QTableWidget::cellDoubleClicked,this,[=](int row,int col){
        if(col==6){
            if(table[row][4]=="cv::Mat"){
                cv::Mat selData=this->workspace->getData(row).getData<cv::Mat>();
                this->popUpMatShow(selData);
            }
            else if(table[row][4]=="PCXYZ"||table[row][4]=="PCXYZRGB"||table[row][4]=="vector<PCXYZRGB>"||table[row][4]=="vector<PCXYZ>"){
                try{
                    int ret=QMessageBox::question(this,tr("important warning"),tr("you are trying to visualize point cloud using PCLVisualizer!\n"
                                                                                 "you should know that there is a certain probability that this\n"
                                                                                  " may crash the application with some uncatchable exception \n"
                                                                                  "especially when the cloud is large. the error reported as \n"
                                                                                  "\"write access violation\", which I have no clue how it happened.\n"
                                                                                 "\n\tdo you insist to visualize the cloud?"),QMessageBox::Yes,QMessageBox::No);
                    if(ret==QMessageBox::Yes){
                        if(!QtPCLViewer::showPointCloud(this->workspace->getData(row))){
                            ui->statusBar->showMessage(tr("the data is null!"));
                        }
                        else{
                            connect(this,&MainWindow::destroyed,[](){
                               QtPCLViewer::terminateAllDisplay();
                            });
                        }
                    }
                }catch(std::exception e){
                    QMessageBox::warning(this,tr("PCLVisualizer exception!"),tr("an exception occurred while try to display point cloud in a visualizer!\nThe exception information is:\n")+e.what(),QMessageBox::Ok);
                }
                catch(...){
                    QMessageBox::warning(this,tr("PCLVisualizer exception!"),tr("an unknown exception occurred while try to display point cloud in a visualizer!"),QMessageBox::Ok);
                }
            }
        }
    });
    //自调整列宽
    for(int i=0;i<ui->tableWidget->columnCount();++i){
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(i,QHeaderView::ResizeToContents);
    }
}

void MainWindow::popUpMatShow(const cv::Mat &img)
{
    if(img.rows>0&&img.cols>0){
        int n=img.channels();
        if(n!=1&&n!=3){//只显示单通道与三通道的图片
            ui->statusBar->showMessage(tr("only images with one or three channel(s) can be displayed!"));
            return;
        }
        cv::namedWindow("Mat show",cv::WINDOW_NORMAL);
        cv::Mat imgShow=img.clone();
        QStringList infos=getMatInfo(imgShow).split("\n");
        if(imgShow.type()!=CV_8UC(n)){
            cv::normalize(imgShow,imgShow,0,255,cv::NORM_MINMAX);
            imgShow.convertTo(imgShow,CV_8UC(n));
        }
        int w=imgShow.cols;
        int h=imgShow.rows;
        float scale=1;
        int max_width=this->width();//以本窗口为最大尺寸
        int max_height=this->height();
        if(h>max_height*0.9||w>max_width*0.9){
            float scale_x=(float)w/max_width/0.9;
            float scale_y=(float)h/max_height/0.9;
            scale=scale_x>scale_y?scale_x:scale_y;
            w=int(float(w)/scale);
            h=int(float(h)/scale);
        }
        int leftMargin=5;
        int fontHeight=15;
        double fontScale=0.5;
        int thickness=1;
        //扩大图片增加文本区域
        cv::Size textSize=cv::getTextSize(infos.at(2).toStdString(),cv::FONT_HERSHEY_SIMPLEX,fontScale*scale,thickness*scale,new int());
        cv::Rect textRect(cv::Point(leftMargin*scale,0),cv::Size(textSize.width,(fontHeight*4+5)*scale));
        int textWidth=textRect.width+leftMargin;
        cv::Mat imgRsz(imgShow.rows+textRect.height,imgShow.cols>textWidth?imgShow.cols:textWidth,imgShow.type(),cv::Scalar::all(0));
        imgShow.copyTo(imgRsz(cv::Range(textRect.height,textRect.height+imgShow.rows),cv::Range(0,imgShow.cols)));
        cv::Point pts[4]={cv::Point(0,textRect.height),cv::Point(imgShow.cols,textRect.height),cv::Point(imgShow.cols,imgRsz.rows-1),cv::Point(0,imgRsz.rows-1)};
        for(int i=0;i<4;++i){
            cv::line(imgRsz,pts[i],pts[(i+1)%4],cv::Scalar(255,255,255));
        }
        imgShow=imgRsz;
        cv::Scalar textColor(255,255,255,255);
        for(int i=0;i<infos.size();++i){
            QString info=infos.at(i);
            cv::putText(imgShow,cv::String(info.toStdString()),cv::Point(leftMargin*scale,fontHeight*(i+1)*scale),cv::FONT_HERSHEY_SIMPLEX,fontScale*scale,textColor,thickness*scale,cv::LINE_AA,false);
        }
        cv::resizeWindow("Mat show",w,h+textRect.height);
        cv::moveWindow("Mat show",this->geometry().left(),this->geometry().top());
        cv::imshow("Mat show",imgShow);
        connect(this,&MainWindow::destroyed,[=](){
           cv::destroyAllWindows();
        });
    }
    else{//图片为空(无行无列)的时候
        QMessageBox::warning(this,tr("access error"),tr("access cv::Mat data in output table failed!\nAssertion failed (size.width>0 && size.height>0) in cv::imshow"),QMessageBox::Ok);
    }
}

QString MainWindow::getMatInfo(cv::Mat img)
{
    //各行分别是rows,cols,type,channels
    QString info="";
    info+="rows:"+QString::number(img.rows)+"\ncols:"+QString::number(img.cols);
    info+="\ntype:";
    int n=img.channels();
    if(img.type()==CV_8UC(n)){
        info+="8UC(n)-8 bit unsigned char";
    }
    else if(img.type()==CV_8SC(n)){
        info+="8SC(n)-8 bit signed char";
    }
    else if(img.type()==CV_16UC(n)){
        info+="16UC(n)-16 bit unsigned short";
    }
    else if(img.type()==CV_16SC(n)){
        info+="16SC(n)-16 bit signed short";
    }
    else if(img.type()==CV_32SC(n)){
        info+="32SC(n)-32 bit signed int";
    }
    else if(img.type()==CV_32FC(n)){
        info+="32FC(n)-32 bit float";
    }
    else if(img.type()==CV_64FC(n)){
        info+="64FC(n)-64 bit double";
    }
    else if(img.type()==CV_16FC(n)){
        info+="16FC(n)";
    }
    else{
        info+="unknown type";
    }
    info+="\nchannels:"+QString::number(img.channels());
    return info;
}

void MainWindow::cellEntered(int row, int col)
{
    this->cellOldValue=ui->tableWidget->item(row,col)->text();
}

void MainWindow::cellChanged(int row, int col)
{
    this->workspace->renameOutput(this->cellOldValue,ui->tableWidget->item(row,col)->text());
}

void MainWindow::on_actionToolBox_toggled(bool arg1)
{
    ui->toolBox->setVisible(arg1);
}

void MainWindow::on_toolBox_visibilityChanged(bool visible)
{
    ui->actionToolBox->setChecked(visible);
}

void Property::setProperty(QString name, QString value)
{
    this->properties[name]=value;
}

QString Property::getProperty(QString name, QString defaultValue)
{
    if(this->properties.contains(name)){
        return this->properties[name];
    }
    else{
        return defaultValue;
    }
}

QString Property::getProperty(QString name)
{
    if(this->properties.contains(name)){
        return this->properties[name];
    }
    else{
        return "";
    }
}

bool Property::propertyExist(QString name)
{
    return this->properties.contains(name);
}

QString Property::getAllInfo()
{
    QString ret;
    for(QString key:this->properties.keys()){
        ret.append(key).append(":  ").append(this->properties[key]).append("\n");
    }
    return ret;
}

void MainWindow::on_workspaceDock_visibilityChanged(bool visible)
{
    ui->actionOutputs->setChecked(visible);
}

void MainWindow::on_actiondoc_triggered()
{
#ifdef Q_OS_WIN32
    QProcess::startDetached("explorer https://blog.csdn.net/liyunxin_c_language/article/details/100894156");
#endif
#ifdef Q_OS_LINUX
    QProcess::startDetached("browse https://blog.csdn.net/liyunxin_c_language/article/details/100894156");
#endif
}

void MainWindow::on_actiontutorial_triggered()
{
#ifdef Q_OS_WIN32
    QProcess::startDetached("explorer https://blog.csdn.net/liyunxin_c_language/article/details/100894119");
#endif
#ifdef Q_OS_LINUX
    QProcess::startDetached("browse https://blog.csdn.net/liyunxin_c_language/article/details/100894119");
#endif
}

void MainWindow::on_actionLoad_L_triggered()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("open plugin library"),sys.getProperty("rootPath"),tr("dynamic library(*.dll)"));
    this->loadPlugin(fileName);
    this->pluginConfig();
    this->arrangeToolBox();
}

void MainWindow::on_actionNew_N_triggered()
{
    QString rootPath=this->sys.getProperty("rootPath");
    QString pluginPath;
    QString pluginName,PLUGIN_NAME,plugin_name;
    QString widgetName,WIDGET_NAME,widget_name;
    QString includePath;
    QString dependPath;
    QString embeded,numInput,numOutput,hasWidget;
    QVector<QString> inputTypes,outTypes,inputDoc,outDoc;
    QString pluginDoc;
    QWizard wizard;
    int n_in,n_out;
    bool has,emb;
    int preId=0;
    //初始页
    QWizardPage *introPage=new QWizardPage();
    introPage->setTitle("Project Name and Path");
    introPage->setSubTitle("designate the plugin name and in which folder to create the project");
    QVBoxLayout *layout1=new QVBoxLayout();
    introPage->setLayout(layout1);
    IntroPageWidget *widgetIntro=new IntroPageWidget();
    widgetIntro->initText("Untitled",this->sys.getProperty("projectPath"));
    layout1->addWidget(widgetIntro);
    //属性页
    QWizardPage *propPage=new QWizardPage();
    propPage->setTitle(tr("Define the properties"));
    propPage->setSubTitle(tr("designate certain behavior of the plugin"));
    QVBoxLayout *layout2=new QVBoxLayout();
    propPage->setLayout(layout2);
    PropPageWidget *widgetProp=new PropPageWidget();
    widgetProp->initProps(true,false,2,2,rootPath+"/include",rootPath+"/dependency");
    layout2->addWidget(widgetProp);
    //确认页
    QWizardPage *confirmPage=new QWizardPage();
    confirmPage->setTitle(tr("Confirm"));
    confirmPage->setSubTitle(tr("\n\n\n\t\tthe following files will be generated:\n\n"));
    QHBoxLayout *layout3=new QHBoxLayout();
    confirmPage->setLayout(layout3);
    QLabel *labelConfirm=new QLabel();
    layout3->addWidget(new QLabel());
    layout3->addWidget(labelConfirm);
    layout3->addWidget(new QLabel());
    //添加页面到向导
    wizard.addPage(introPage);
    wizard.addPage(propPage);
    wizard.addPage(confirmPage);
    wizard.setWindowTitle("Create New Plugin");
    wizard.setMinimumSize(propPage->width(),propPage->height());
    connect(&wizard,&QWizard::currentIdChanged,[&](int id){
        if(preId==0&&id==1){
            pluginPath=widgetIntro->getProjectPath();
            pluginName=widgetIntro->getProjectName();
            PLUGIN_NAME=pluginName.toUpper();
            plugin_name=pluginName.toLower();
            widgetName=pluginName+"Widget";
            WIDGET_NAME=widgetName.toUpper();
            widget_name=widgetName.toLower();
        }
        if(preId==1&&id==2){//切换到确认页
            widgetProp->getProps(has,emb,n_in,n_out,includePath,dependPath,inputTypes,outTypes,inputDoc,outDoc,pluginDoc);
            if(has){
                hasWidget="true";
            }
            else{
                hasWidget="false";
            }
            if(emb){
                embeded="true";
            }
            else{
                embeded="false";
            }
            numInput=QString::number(n_in);
            numOutput=QString::number(n_out);
            QString conf="\n\n";
            conf+=pluginName+".pro\n";
            conf+=plugin_name+"_global.h\n";
            conf+=plugin_name+".h\n";
            conf+=plugin_name+".cpp\n";
            if(has){
                conf+=widget_name+".h\n";
                conf+=widget_name+".cpp\n";
                conf+=widget_name+".ui\n\n";
            }
            labelConfirm->setText(conf);
        }
        preId=id;
    });
    if(wizard.exec()==QDialog::Accepted){
        QDir dir(pluginPath+"/"+pluginName);
        if(dir.exists()){
            int ret=QMessageBox::question(this,tr("create project"),tr("Project name conflict with existing folder under current directory!\nDo you want to override?"),QMessageBox::Yes,QMessageBox::No);
            if(ret=QMessageBox::Yes){
                dir.removeRecursively();
                dir.mkdir(dir.path());
            }
            else{
                return;
            }
        }
        else{
            dir.mkdir(dir.path());
        }
        auto stringReplace=[=](QString text)->QString{
            QString result=text;
            if(has){
                result=result.replace("PROP_HASWIDGET_AUTO_REPLACED","pluginWidget");
            }
            else{
                result=result.replace("PROP_HASWIDGET_AUTO_REPLACED","NULL");
                //去掉不需要的
                result=result.replace("#include <FILE_WIDGET_AUTO_REPLACED.h>","");
                result=result.replace("PLUGIN_WIDGET_AUTO_REPLACED *pluginWidget;","");
                result=result.replace("pluginWidget=new PLUGIN_WIDGET_AUTO_REPLACED();","");
                result=result.replace("FILE_WIDGET_AUTO_REPLACED.cpp","");
                result=result.replace("FILE_WIDGET_AUTO_REPLACED.h","");
                result=result.replace("FORMS += \\","");
                result=result.replace("FILE_WIDGET_AUTO_REPLACED.ui","");
            }
            result=result.replace("PLUGIN_NAME_AUTO_REPLACED",pluginName);//替换插件名
            result=result.replace("TARGET_NAME_AUTO_REPLACED",PLUGIN_NAME);//替换全大写的插件名
            result=result.replace("FILE_NAME_AUTO_REPLACED",plugin_name);//替换全小写的插件名
            result=result.replace("PLUGIN_WIDGET_AUTO_REPLACED",widgetName);//替换widget名
            result=result.replace("TARGET_WIDGET_AUTO_REPLACED",WIDGET_NAME);//替换全大写的widget名
            result=result.replace("FILE_WIDGET_AUTO_REPLACED",widget_name);//替换全小写的widget名
            result=result.replace("TIME_STAMP_AUTO_REPLACED",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));//替换时间戳
            result=result.replace("QPCPLATFORM_INCLUDEPATH_AUTO_REPLACED",includePath);//替换包含目录
            result=result.replace("REFLEX_PATH_AUTO_REPLACED",dependPath);//替换反射机制库依赖目录
            result=result.replace("IPLUGIN_PATH_AUTO_REPLACED",dependPath);//替换插件接口库依赖目录
#ifdef QT_NO_DEBUG
            result=result.replace("DEBUG_DLL_PATH_AUTO_REPLACED","$$PWD/debug");
            result=result.replace("RELEASE_DLL_PATH_AUTO_REPLACED",sys.getProperty("rootPath")+"/plugins");
#else
            result=result.replace("DEBUG_DLL_PATH_AUTO_REPLACED",sys.getProperty("rootPath")+"/plugins");
            result=result.replace("RELEASE_DLL_PATH_AUTO_REPLACED","$$PWD/release");
#endif
            result=result.replace("PROP_EMBEDED_AUTO_REPLACED",embeded);//替换是否内嵌界面属性
            result=result.replace("PROP_INPUT_AUTO_REPLACED",numInput);//替换输入参数个数
            result=result.replace("PROP_OUTPUT_AUTO_REPLACED",numOutput);//替换输出参数个数
            QString inTypeStr="";
            for(int i=0;i<inputTypes.size();++i){
                inTypeStr+="inputTypes.push_back(\""+TypeNameDisplayer::fromDisplay(inputTypes[i])+"\");\n    ";
            }
            result=result.replace("INPUT_TYPES_AUTO_REPLACED",inTypeStr);//替换输入参数类型字符串
            QString outTypeStr="";
            for(int i=0;i<outTypes.size();++i){
                outTypeStr+="outputTypes.push_back(\""+TypeNameDisplayer::fromDisplay(outTypes[i])+"\");\n    ";
            }
            result=result.replace("OUTPUT_TYPES_AUTO_REPLACED",outTypeStr);//替换输出类型字符串
            QString inDocStr="";
            for(int i=0;i<inputDoc.size()&&inputDoc[i]!="";++i){
                inDocStr+="info.push_back(\""+inputDoc[i]+"\");\n    ";
            }
            result=result.replace("INPUT_DESCRIPT_AUTO_REPLACED",inDocStr);//替换输入参数信息
            QString outDocStr="";
            for(int i=0;i<outDoc.size()&&outDoc[i]!="";++i){
                outDocStr+="info.push_back(\""+outDoc[i]+"\");\n    ";
            }
            result=result.replace("OUTPUT_DESCRIPT_AUTO_REPLACED",outDocStr);//替换输出参数信息
            result=result.replace("PLUGIN_DOC_AUTO_REPLACED","\""+pluginDoc+"\"");
            return result;
        };
        auto toFile=[=](QString content,QString fileName){
            content=stringReplace(content);
            QFile file(fileName);
            bool opened=file.open(QIODevice::WriteOnly|QFile::Truncate);
            if(opened){
                QTextStream ts(&file);
                ts<<content;
                ts.setCodec("utf-8");
                ts.flush();
                file.close();
            }
        };
        try{
            QFile proFile(this->sys.getProperty("rootPath")+"/templates/template.pro");
            proFile.open(QFile::ReadOnly);
            QFile pluginGH(this->sys.getProperty("rootPath")+"/templates/plugin_template_global.h");
            pluginGH.open(QFile::ReadOnly);
            QFile pluginH(this->sys.getProperty("rootPath")+"/templates/plugin_template.h");
            pluginH.open(QFile::ReadOnly);
            QFile pluginCpp(this->sys.getProperty("rootPath")+"/templates/plugin_template.cpp");
            pluginCpp.open(QFile::ReadOnly);
            QTextStream ts1(&proFile);
            ts1.setCodec("utf-8");
            toFile(ts1.readAll(),pluginPath+"/"+pluginName+"/"+pluginName+".pro");
            proFile.close();
            QTextStream ts2(&pluginGH);
            ts2.setCodec("utf-8");
            toFile(ts2.readAll(),pluginPath+"/"+pluginName+"/"+plugin_name+"_global.h");
            pluginGH.close();
            QTextStream ts3(&pluginH);
            ts3.setCodec("utf-8");
            toFile(ts3.readAll(),pluginPath+"/"+pluginName+"/"+plugin_name+".h");
            pluginH.close();
            QTextStream ts4(&pluginCpp);
            ts4.setCodec("utf-8");
            toFile(ts4.readAll(),pluginPath+"/"+pluginName+"/"+plugin_name+".cpp");
            pluginCpp.close();
            if(has){
                QFile widgetUI(this->sys.getProperty("rootPath")+"/templates/widget_template.ui");
                widgetUI.open(QFile::ReadOnly);
                QFile widgetH(this->sys.getProperty("rootPath")+"/templates/widget_template.h");
                widgetH.open(QFile::ReadOnly);
                QFile widgetCpp(this->sys.getProperty("rootPath")+"/templates/widget_template.cpp");
                widgetCpp.open(QFile::ReadOnly);
                QTextStream ts5(&widgetUI);
                ts5.setCodec("utf-8");
                toFile(ts5.readAll(),pluginPath+"/"+pluginName+"/"+widget_name+".ui");
                widgetUI.close();
                QTextStream ts6(&widgetH);
                ts6.setCodec("utf-8");
                toFile(ts6.readAll(),pluginPath+"/"+pluginName+"/"+widget_name+".h");
                widgetH.close();
                QTextStream ts7(&widgetCpp);
                ts7.setCodec("utf-8");
                toFile(ts7.readAll(),pluginPath+"/"+pluginName+"/"+widget_name+".cpp");
                widgetCpp.close();
            }
            QString cmd="explorer file://"+pluginPath+"/"+pluginName;
            QProcess::startDetached(cmd);
        }catch(std::exception &e){
            QMessageBox::warning(this,tr("Error"),tr("something happeded when open template files or create project files\nerror:\n")+QString::fromStdString(e.what()),QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_actionOutputs_toggled(bool arg1)
{
    ui->workspaceDock->setVisible(arg1);
}
