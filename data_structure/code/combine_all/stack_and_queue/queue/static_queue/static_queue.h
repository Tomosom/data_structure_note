#ifndef STATIC_QUEUE_H
#define STATIC_QUEUE_H

#include "queue.h"
#include "exception.h"

namespace DTLib {

template <typename T, int N>
class StaticQueue : public Queue<T> {
protected:
    T m_space[N];   // 队列存储空间，N为模板参数
    int m_front;    // 队头标识
    int m_rear;       // 队尾标识
    int m_length;   // 当前队列的长度

public:
    StaticQueue()   // 初始化成员变量
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int capacity() const
    {
        return N;
    }

    void add(const T &e) // O(1)
    {
        if (m_length < N) {
            m_space[m_rear] = e;
            m_rear = (m_rear + 1) % N;
            m_length++;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No space in current queue ...");
        }
    }

    void remove() // O(1)
    {
        if (m_length > 0) {
            m_front = (m_front + 1) % N;
            m_length--;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const // O(1)
    {
        if (m_length > 0) {
            return m_space[m_front];
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    void clear() // O(1)
    {
        m_front = 0;
        m_rear = 0;
        m_length = 0;
    }

    int length() const // O(1)
    {
        return m_length;
    }

};

}

#endif