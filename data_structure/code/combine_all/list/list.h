#ifndef LIST_H
#define LIST_H

#include "object.h"

namespace DTLib {

template <typename T>
class List : public Object {
protected:
	List(const List&); // 禁用拷贝构造函数, 有了此句，编译器不会提供默认的构造函数了
	List &operator=(const List&); // 禁用顺序表对象之间赋值

public:
	List(){ }
	virtual bool insert(const T &e) = 0; // 默认在线性表的尾部插入函数
	virtual bool insert(int i, const T &e) = 0;
	virtual bool remove(int i) = 0;
	virtual bool set(int i, const T &e) = 0;
	virtual bool get(int i, T &e) const = 0;
    virtual int find(const T &e) const = 0;
	virtual int length() const = 0;
	virtual void clear() = 0;

};




}



#endif