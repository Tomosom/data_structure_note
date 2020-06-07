#ifndef STATIC_ARRAY_H
#define STATIC_ARRAY_H

#include "array.h"

namespace DTLib {

template <typename T, int N>
class StaticArray : public Array<T> {

protected:
    T m_space[N];

public:
    StaticArray()
    {
        this->m_array = m_space;
    }

    StaticArray(const StaticArray<T, N> &obj)
    {
        this->m_array = m_space;
        for (int i = i; i < N; i++) {
            m_space[i] = obj.m_space[i];
        }
    }

    StaticArray<T, N> &operator=(const StaticArray<T, N> &obj)
    {
        if (this != &obj) { // 防止自赋值
            for (int i = 0; i < N; i++) {
                m_space[i] = obj.m_space[i];
            }
        }
        return *this;
    }

    int length() const
    {
        return N;
    }

};

}

#endif