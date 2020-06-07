#ifndef _SMART_POINT_H_
#define _SMART_POINT_H_

#include "pointer.h"

namespace DTLib
{
template<typename T>
class SmartPointer : public Pointer<T> {

public:
	SmartPointer(T *p = NULL) : Pointer<T>(p) // 调用父类的构造函数
	{
	}

	SmartPointer(const SmartPointer<T> &obj)
	{
		this->m_pointer = obj.m_pointer;
		const_cast<SmartPointer<T>&>(obj).m_pointer = NULL;
	}

	SmartPointer<T>& operator=(const SmartPointer<T> &obj)
	{
		if (this != &obj)
		{
		    T *p = this->m_pointer;
			this->m_pointer = obj.m_pointer;
			const_cast<SmartPointer<T>&>(obj).m_pointer = NULL; //保证只有一个smartpointer指向改指针
            delete p;
        }
		return *this;
	}

	~SmartPointer()
	{
		delete this->m_pointer;
	}

};

}


#endif /* end of _SMART_POINT_H_ */
