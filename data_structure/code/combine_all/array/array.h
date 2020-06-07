#ifndef ARRAY_H
#define ARRAY_H

#include "exception.h"

namespace DTLib {

template <typename T>
class Array : public Object {
protected:
    T *m_array;

public:
    virtual bool set(int i, const T &e)
    {
        bool ret = ((0 <= i) && (i < length()));
        if (ret) {
            m_array[i] = e;
        }

        return ret;
    }
    virtual bool get(int i, T &e) const {
        bool ret = ((0 <= i) && (i < length()));
        if (ret) {
            e = m_array[i];
        }

        return ret;
    }

    /* 数组访问操作符 */
    T &operator[] (int i)
    {
        if ((0 <= i) && (i < length())) {
            return m_array[i];
        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Param i is invalid ...");
        }
    }
    T operator[] (int i) const
    {
        return (const_cast<Array<T>&>(*this))[i];
    }

    /* 为了将排序类(Sort)应用于该数组类，固需新增一个成员函数 */
    T *array() const // 返回所封装的原生数组的首地址
    {
        return  m_array;
    }

    virtual int length() const = 0;

};






}




#endif