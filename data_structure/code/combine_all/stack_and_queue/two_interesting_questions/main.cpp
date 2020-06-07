#include <iostream>
#include "link_stack.h"
#include "link_queue.h"

using namespace std;
using namespace DTLib;

template <typename T>
class StackToQueue : public Queue<T> {
protected:
    mutable LinkStack<T> m_stack_in;
    mutable LinkStack<T> m_stack_out;

    void move() const // O(n)
    {
        if (m_stack_out.size() == 0) {
            while(m_stack_in.size() > 0) {
                m_stack_out.push(m_stack_in.top());
                m_stack_in.pop();
            }
        }
    }

public:
    void add(const T &e) // O(1)
    {
        m_stack_in.push(e);
    }

    void remove() // O(n)
    {
        move();

        if (m_stack_out.size() > 0) {
            m_stack_out.pop();
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }

    T front() const // O(n)
    {
        move();

        if (m_stack_out.size() > 0) {
            return m_stack_out.top();
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current queue ...");
        }
    }
    void clear() // O(n)
    {
        m_stack_in.clear();
        m_stack_out.clear();
    }

    int length() const // O(1)
    {
        return m_stack_in.size() + m_stack_out.size();
    }


};

template <typename T>
class QueueToStack : public Stack<T> {
protected:
    LinkQueue<T> m_queue_1;
    LinkQueue<T> m_queue_2;

    LinkQueue<T> *m_pIn;
    LinkQueue<T> *m_pOut;

    void move() const // O(n)
    {
        int n = m_pIn->length() - 1;

        for(int i = 0; i < n; i++) {
            m_pOut->add(m_pIn->front());
            m_pIn->remove();
        }
    }

    void swap() // O(1)
    {
        LinkQueue<T> *temp = NULL;
        temp = m_pIn;
        m_pIn = m_pOut;
        m_pOut = temp;
    }

public:
    QueueToStack() // O(1)
    {
        m_pIn = &m_queue_1;
        m_pOut = &m_queue_2;
    }

    void push(const T &e) // O(1)
    {
        m_pIn->add(e);
    }

    void pop() // O(n)
    {
        if(m_pIn->length() > 0) {
            move();
            m_pIn->remove();
            swap();
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }

    T top() const // O(n)
    {
        if(m_pIn->length() > 0) {
            move();
            return m_pIn->front();
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No element in current stack ...");
        }
    }
    
    void clear() // O(n)
    {
        m_queue_1.clear();
        m_queue_2.clear();
    }

    int size() const // O(1)
    {
        return m_queue_1.length() + m_queue_2.length();
    }

};

int main(int argc, char **acgv)
{
    cout << "### StackToQueue ###" << endl;
    StackToQueue<int> sq;

    for(int i = 0; i < 10; i++) {
        sq.add(i);
    }

    while(sq.length() > 0) {
        cout << sq.front() << endl;
        sq.remove();
    }

    cout << "### QueueToStack ###" << endl;
    QueueToStack<int> qs;

    for(int i = 0; i < 10; i++) {
        qs.push(i);
    }

    while(qs.size() > 0) {
        cout << qs.top() << endl;
        qs.pop();
    }

    return 0;
}
