#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "seq_list.h"
#include "exception.h"

namespace DTLib {
	
	
template <typename T>
class DynamicList : public SeqList<T> {
protected:
	int m_capacity; // 顺序存储空间的大小
	
public:
	DynamicList(int capacity) //申请空间
	{
		this->m_array = new T[capacity];
		if (this->m_array != NULL) {
			this->m_length = 0;
			this->m_capacity = capacity;
		} else {
			THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat DynamicList object ...");
		}
	}
	
	int capacity() const
	{
		return m_capacity;
	}
	
	// 重新设置顺序存储空间的大小
	void resize(int capacity)
	{
		if (capacity != m_capacity) {
			T *array = new T[capacity];
			if (array != NULL) {
				int length = this->m_length < capacity ? this->m_length : capacity;
				
				for(int i = 0; i < length; i++) {
					array[i] = this->m_array[i];
				}
				
				T *temp = this->m_array;
				this->m_array = array;
				this->m_length = length;
				this->m_capacity = capacity;
				
				delete[] temp; // 若T是一个类，此操作调用析构。可能抛出异常，固定义temp
			} else {
				THROW_EXCEPTION(NoEnoughMemoryException, "No memory to creat DynamicList object ...");
			}
		}
	}
	
	
	~DynamicList() //归还空间
	{
		delete[] this->m_array;
	}
	
};
	
	
	
	
	
	
	
	
	
	
	
}


#endif
