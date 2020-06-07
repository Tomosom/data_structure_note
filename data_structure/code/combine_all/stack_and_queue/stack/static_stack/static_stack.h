#ifndef STATIC_STACK_H
#define STATIC_STACK_H

#include "stack.h"
#include "exception.h"

namespace DTLib {

template <typename T, int N>
class StaticStack : public Stack<T> {
protected:
    T m_space[N];   // 栈存储空间，N为模板参数
    int m_top;      // 栈顶标识
    int m_size;     // 当前栈的大小

public:
    StaticStack() // O(1)
    {
        m_top = -1;
        m_size = 0;
    }

    int capacity() const // O(1)
    {
        return N;
    }

    void push(const T &e) // O(1)
    {
        if (m_size < N)
        {
            m_space[m_top + 1] = e; // 异常安全，以免e的等号操作异常
            m_top++;
            m_size++;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No space in current stack...");
        }
    }

    void pop() // O(1)
    {
        if(m_size > 0) {
            m_top--;
            m_size--;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
        }
    }

    T top() const // O(1)
    {
        if(m_size > 0) {
            return m_space[m_top];
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack...");
        }
    }

    void clear() // O(1)
    {
        m_top = -1;
        m_size = 0;
    }

    int size() const // O(1)
    {
        return m_size;
    }

};

}

#endif