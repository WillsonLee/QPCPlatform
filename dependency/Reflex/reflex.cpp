#include "reflex.h"

std::string Factory::justAddedClass("");//default value is empty when no class is added to the register map

Factory::~Factory()
{
    for (; m_classInfoMap->size() > 0;) { delete (*m_classInfoMap)[0]; m_classInfoMap->erase(0); }
}

bool Factory::Register(ClassInfo * pCInfo)
{
    if (!m_classInfoMap) {
        m_classInfoMap = new std::map<std::string, ClassInfo*>();
    }
    if (!pCInfo) {
        return false;
    }
    if (m_classInfoMap->end() == m_classInfoMap->find(pCInfo->GetClassName())) {
        m_classInfoMap->insert(std::map<std::string, ClassInfo*>::value_type(pCInfo->GetClassName(), pCInfo));
        justAddedClass=pCInfo->GetClassName();
    }
    return true;
}

bool Factory::Unregister(std::string className)
{
    if(m_classInfoMap){
        auto iter=m_classInfoMap->find(className);
        if(m_classInfoMap->end()!=iter){
            m_classInfoMap->erase(iter);
            return true;
        }
    }
    //unregister failed because the class to be unregistered is not registered at first place
    return false;
}

std::string Factory::getNewAddedClassName()
{
    return justAddedClass;
}

std::vector<std::string> *Factory::GetClassNames()
{
    std::vector<std::string>* keys=new std::vector<std::string>();
    if(m_classInfoMap){
        for(auto c_iter=m_classInfoMap->begin();c_iter!=m_classInfoMap->end();++c_iter){
            keys->push_back(c_iter->first);
        }
    }
    return keys;
}

ReflexBase * Factory::CreateObject(std::string className)
{
    if(!m_classInfoMap)return NULL;
    std::map<std::string, ClassInfo*>::const_iterator c_iter = m_classInfoMap->find(className);
    if (m_classInfoMap->end() != c_iter) {
        return c_iter->second->CreateObject();
    }
    return NULL;
}

ClassInfo * Factory::GetClassInfo(std::string className)
{
    if(!m_classInfoMap)return NULL;
    std::map<std::string, ClassInfo*>::const_iterator c_iter = m_classInfoMap->find(className);
    if (m_classInfoMap->end() != c_iter) {
        return c_iter->second;
    }
    return NULL;
}
