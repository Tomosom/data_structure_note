#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "seq_list.h"

namespace DTLib {
	
template <typename T, int N>
class StaticList : public SeqList<T> {
protected:
	T m_space[N]; // 顺序存储空间，N为模板参数

public:
	StaticList() // 指定父类成员的具体值
	{
		this->m_array = m_space;
		this->m_length = 0;
	
	}
	int capacity() const
	{
		return N;
	}
};
	
}


#endif