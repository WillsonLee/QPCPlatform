#ifndef ANY_H
#define ANY_H
#include <string>
#ifdef linux
#include <cxxabi.h>
#endif

#define TYPENAMEOFSTRING "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >"

/**\brief 抹除类型的数据载体，用于保存任意类型数据的地址及其类型名称
  */
class Any
{
public:
    Any() :pData(NULL), type("null") {}
    template<class ValueType>
    Any(const ValueType& value) { setData(value); }
    /**\brief 保存任意数据value(如果value也是Any类型，则保存value中保存的数据)
    */
    /**
     * @brief 保存任意数据value(如果value也是Any类型，则保存value中保存的数据)
     */
    template<class ValueType>
    Any& setData(const ValueType& value) { pData = (void*)(&value); type = typeid(value).name();return *this; }
    /**\brief 取出Any中保存的数据于value中，成功则返回true否则false(如果value也是Any类型，则让value保存相同的数据)
    */
    template<class ValueType>
    bool getData(ValueType& dst) { if (!isCompatible(dst))return false; if(this->pData==&dst)return true;dst = *(ValueType*)(pData); return true; }
    /**\brief 取出数据
     * \优点:该函数与带参数的不同的是带参数的是返回经过=运算符赋值的数据(有的数据在这里可能会复制,导致大量数据的冗余)
     * \缺点:不能进行类型检查,Any中保存的可能不是指定的ValueType数据,按照该类型返回可能出错
    */
    template<class ValueType>
    ValueType& getData(){return *(ValueType*)(pData);}
    /**\brief 断any中的数据与value类型是否一样(如果value也是Any类型，any的type为null即没有保存数据时,返回true;any的type不为null需要二者type一样时才返回true)
    */
    template<class ValueType>
    bool isCompatible(const ValueType& value) { return (std::string)(typeid(value).name()) == std::string(this->type); }
    /**\brief 判断any中的数据与value类型是否一样（如果value也是Any类型，any与value必须都不为null且类型相同才返回true）
     */
    template<class ValueType>
    bool ofSameType(const ValueType& value) { return isCompatible(value);}
    /**\brief 获取数据地址
    */
    void* getAddress() { return pData; }
    /**\brief 获取数据类型
    */
    const std::string getType() {
#ifdef _WIN32
        return std::string(type);
#endif
#ifdef linux
        int status;
        char *ch=abi::__cxa_demangle(type,0,0,&status);
        std::string t=ch==NULL?"null":std::string(ch);
        return t;
#endif
    }
    /**\brief 判断any中是否未保存数据
    */
    bool isNull() { return pData == NULL; }
    /**\brief 判断any中保存的数据与value是否一致(如果value也是Any类型则判断二者保存的数据是否一致)
    */
    template<class ValueType>
    bool isSameAs(ValueType& value){return pData==(void*)(&value)&&type==typeid(value).name();}
    /**\brief 将Any重置(指向NULL)
    */
    Any& reset(){this->pData=NULL;this->type="null";return *this;}
    /**\brief 执行清除内存块操作,不但重置Any对象,且将其指向的内存也清理
     * \note:这个函数安全性是有问题的,因为Any对选哪个也可保存栈上的数据,但是delete栈上数据会出错;请务必确保数据在堆上才使用该清理函数
    */
    template<class ValueType>
    void clean(){if(pData!=NULL){ValueType *ptr=(ValueType*)pData;delete ptr;reset();}}
private:
    void* pData;
    const char* type;
};

template<> inline Any& Any::setData<Any>(const Any& value) {this->pData = value.pData; this->type = value.type;return *this;}
template<> inline bool Any::getData(Any &dst){dst.pData=this->pData;dst.type=this->type;return true;}
template<> inline Any& Any::getData<Any>(){return Any().setData(*this);}
template<> inline bool Any::isSameAs<Any>(Any &another){return this->pData==another.pData&&this->type==another.type;}
template<> inline bool Any::isCompatible(const Any &dst){if(std::string(this->type)=="null")return true;return std::string(this->type)==std::string(dst.type);}
template<> inline bool Any::ofSameType(const Any &dst){if(std::string(this->type)!="null"&&std::string(dst.type)!="null"&&std::string(this->type)==std::string(dst.type))return true;else return false;}


#endif
