/**\brief 该头文件用于实现简化的反射机制，用于实现插件拓展功能
 * \用法为：
 * \1.定义插件的基类IPlugin使其继承自ReflexBase类
 * \2.定义插件时使其继承自IPlugin基类，同时在插件类定义结尾处使用宏CONSTRUCTOR(class_name),该宏功能是创建统一的插件实例生成方式
 * \3.在插件类定义完了紧接着使用REGISTER_REFLEX(class_name)注册插件类即实现其反射信息的保存
 * \4.主程序调用插件时使用Factory::GetClassNames()获取所有注册了反射机制的插件的名称;使用Factory::CreateObject(className)获取名称为className的插件实例的指针
*/
#ifndef REFLEX_H
#define REFLEX_H

#include "reflex_global.h"
#include <string>
#include <map>
#include <vector>

#define CONSTRUCTOR(class_name)\
public:\
static ReflexBase* CreateObject()\
{\
    return new class_name;\
}\
protected:\
static ClassInfo m_classInfo;

#define REGISTER_REFLEX(class_name)\
ClassInfo class_name::m_classInfo(#class_name,class_name::CreateObject);

class REFLEXSHARED_EXPORT ClassInfo;
class REFLEXSHARED_EXPORT ReflexBase;
static std::map<std::string, ClassInfo*> *m_classInfoMap;

class REFLEXSHARED_EXPORT Factory
{
public:
    Factory() {}
    ~Factory();
    static bool Register(ClassInfo *pCInfo);
    static bool Unregister(std::string className);
    static std::string getNewAddedClassName();
    static std::vector<std::string>* GetClassNames();
    static ReflexBase* CreateObject(std::string className);
    static ClassInfo* GetClassInfo(std::string className);
private:
    static std::string justAddedClass;
};
typedef ReflexBase* (*objConstructorFun)();
class ClassInfo
{
public:
    ClassInfo(const std::string className, objConstructorFun classConstructor) :
        m_className(className), m_objConstructor(classConstructor)
    {
        Factory::Register(this);
    }
    virtual ~ClassInfo() {}
    ReflexBase* CreateObject()const { return m_objConstructor ? (*m_objConstructor)() : NULL; }
    bool IsDynamic()const { return NULL != m_objConstructor; }
    const std::string GetClassName()const { return this->m_className; }
    objConstructorFun GetConstructor()const { return this->m_objConstructor; }
private:
    std::string m_className;
    objConstructorFun m_objConstructor;
};

class ReflexBase
{
public:
    ReflexBase() {}
    virtual ~ReflexBase() {}
};

#endif // REFLEX_H
