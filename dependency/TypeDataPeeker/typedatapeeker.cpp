#include "typedatapeeker.h"


TypeDataPeeker::TypeDataPeeker()
{
}

QString TypeDataPeeker::peek(Any data)
{
    QString value;
    try{
        if(type(data)=="int"){
            value=QString::number(data.getData<int>());
        }
        else if(type(data)=="unsigned int"){
            value=QString::number(data.getData<uint>());
        }
        else if(type(data)=="float"){
            value=QString::number(data.getData<float>());
        }
        else if(type(data)=="double"){
            value=QString::number(data.getData<double>());
        }
        else if(type(data)=="long"){
            value=QString::number(data.getData<long>());
        }
        else if(type(data)==TYPENAMEOFSTRING){
            value=QString::fromStdString(data.getData<std::string>());
        }
        else if(type(data)=="bool"){
            value=data.getData<bool>()?"true":"false";
        }
        else if(type(data)=="class QString"){
            value=data.getData<QString>();
        }
        else{
            value="unknown";
        }
    }
    catch(std::exception e){
        value="peek failed";
    }
    return value;
}

QString TypeDataPeeker::type(Any data)
{
    return QString::fromStdString(std::string(data.getType()));
}
