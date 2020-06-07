/*
 * 该智能指针的使用军规：
 * 只能用来指向堆空间中的单个变量
 * 不同类型的智能指针对象不能混合使用
 * 不要使用delete释放智能指针指向的堆空间
 */

#ifndef POINTER_H
#define POINTER_H

#include "object.h"

namespace DTLib {

template <typename T>
class Pointer : public Object {

protected:
    T *m_pointer;


public:
    Pointer(T *p = NULL)
    {
        m_pointer = p;
    }

    const T *operator->() const
    {
        return m_pointer;
    }

    const T &operator*() const
    {
        return *m_pointer;
    }

    T *operator->()
    {
        return m_pointer;
    }

    T &operator*()
    {
        return *m_pointer;
    }

    bool isNull()
    {
        return (m_pointer == NULL);
    }

    T *get() const
    {
        return m_pointer;
    }

    // 因未实现析构函数，因此该类也是一个模板类
};



}



#endif
