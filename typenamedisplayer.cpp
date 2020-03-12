#include "typenamedisplayer.h"
#include <Any.h>

QMap<QString,QString> TypeNameDisplayer::typeToDisplay=QMap<QString,QString>();
QMap<QString,QString> TypeNameDisplayer::displayToType=QMap<QString,QString>();

TypeNameDisplayer::TypeNameDisplayer()
{

}

void TypeNameDisplayer::initMaps()
{
    if(TypeNameDisplayer::typeToDisplay.size()>0){
        return;//无需重复初始化
    }
    TypeNameDisplayer::typeToDisplay["int"]="int";
    TypeNameDisplayer::typeToDisplay["float"]="float";
    TypeNameDisplayer::typeToDisplay["double"]="double";
    TypeNameDisplayer::typeToDisplay[TYPENAMEOFSTRING]="string";
    TypeNameDisplayer::typeToDisplay["long"]="long";
    TypeNameDisplayer::typeToDisplay["class cv::Mat"]="cv::Mat";
    for(auto key:TypeNameDisplayer::typeToDisplay.keys()){
        TypeNameDisplayer::displayToType[TypeNameDisplayer::typeToDisplay[key]]=key;
    }
}

QString TypeNameDisplayer::toDisplay(QString name)
{
    //该函数将类型名称字符串转化成更为简短的显示名称
    if(TypeNameDisplayer::typeToDisplay.contains(name)){
        return TypeNameDisplayer::typeToDisplay[name];
    }
    return name;
}

QString TypeNameDisplayer::fromDisplay(QString name)
{
    if(TypeNameDisplayer::displayToType.contains(name)){
        return TypeNameDisplayer::displayToType[name];
    }
    return name;
}

QStringList TypeNameDisplayer::allDisplayTypeStrings()
{
    QStringList list(TypeNameDisplayer::displayToType.keys());
    return list;
}

void TypeNameDisplayer::addTypeStrMap(QString type, QString display)
{
    if(!TypeNameDisplayer::typeToDisplay.contains(type)&&!TypeNameDisplayer::displayToType.contains(display)){
        TypeNameDisplayer::typeToDisplay[type]=display;
        TypeNameDisplayer::displayToType[display]=type;
    }
}
