#ifndef PCSERIALIZER_H
#define PCSERIALIZER_H

#include "pcserializer_global.h"
#include <Any.h>
#include <iplugin.h>
#include <reflex.h>
#include <pcserializerwidget.h>
#include <QString>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>

class PCSERIALIZERSHARED_EXPORT PCSerializer:public IPlugin
{
public:
    PCSerializer();

    // IPlugin interface
public:
    int getInputCount();
    std::vector<std::string> getInputTypes();
    int getOutputCount();
    std::vector<std::string> getOutputTypes();
    void run();
    void cleanGarbage(std::vector<Any> &outputVars, const std::vector<int> targets);
    QWidget *getWidget();
    std::string saveState();
    bool restoreState(std::string stateFile);
    std::string getDoc();
    std::vector<std::string> getInputInfo();
    std::vector<std::string> getOutputInfo();
private:
    //定义内部参数
    PCSerializerWidget *pluginWidget;
    QString folderName;
	//反射构造器后面不要加语句,如果要加,要用public,private,protected等权限符隔开
    CONSTRUCTOR(PCSerializer)
};
REGISTER_REFLEX(PCSerializer)

#endif // TESTPLUGIN_H
