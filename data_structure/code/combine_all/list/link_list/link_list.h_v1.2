#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "list.h"
#include "exception.h"
namespace DTLib {


template <typename T>
class LinkList : public List<T> {

protected:
    struct Node : public Object {
        T value;
        Node *next;
    };

    //mutable Node m_header;
    //dt way 避免泛型类型T构造函数的调用
    mutable struct : public Object { // 也必须继承object，不然内存结构不一致
        char reserved[sizeof(T)];
        Node *next;
    } m_header;

    int m_length;
    int m_step; // 游标每次移动节点的数目
    Node *m_current; // 游标

    Node *position(int i) const
    {
        Node *ret = reinterpret_cast<Node *>(&m_header);
        for(int p = 0; p < i; p++) {
            ret = ret->next;
        }
        return ret;
    }

    virtual Node *create()
    {
        return new Node();
    }

    virtual void destroy(Node *pn)
    {
        delete pn;
    }

public:
    LinkList()
    {
        m_header.next = NULL;
        m_length = 0;
        m_step = 1;
        m_current = NULL;
    }


	bool insert(const T &e)
    {
        return insert(m_length, e);
    }

	bool insert(int i, const T &e)
    {
        bool ret = ((0 <= i) && (i <= m_length));
        if (ret) {
            Node *node = create();
            if(node != NULL) {
                Node *current = position(i);

                node->value = e;
                node->next = current->next;
                current->next = node;

                m_length++;
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element");
            }
        }
    }
	bool remove(int i)
    {
        bool ret = ((0 <= i) && (i < m_length));
        if (ret) {
            Node *current = position(i);

            Node *toDel = current->next;
            current->next = toDel->next;
            destroy(toDel);
            m_length--;
        }

        return ret;
    }

	bool set(int i, const T &e)
    {
        bool ret = ((0 <= i) && (i < m_length));
        if (ret) {
            Node *current = position(i);
            current->next->value = e;
        }
        return ret;
    }

    T get(int i) const
    {
        T ret;
        if (get(i, ret)) {
            return ret;
        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Incalid parameter i to get element...");
        }
        return ret;
    }

	bool get(int i, T &e) const
    {
        bool ret = ((0 <= i) && (i < m_length));
        if (ret) {
            Node *current = position(i);
            e = current->next->value ;
        }
        return ret;
    }
	int length() const
    {
        return m_length;
    }

    int find(const T &e) const
    {
        int ret = -1;
        int i = 0;
        Node *node = m_header.next;

        while(node) {
            if (node->value == e) {
                ret = i;
                break;
            } else {
                node = node->next;
                i++;
            }
        }

        return ret;
    }

	void clear()
    {
        while(m_header.next) {
            Node *toDel = m_header.next;

            m_header.next = toDel->next;

            delete toDel;

        }
        m_length = 0;
    }

    // 将游标定位到目标位置
    bool move(int i, int step = 1)
    {
        bool ret = (0 <= i) && (i < m_length) && (step > 0);
        if (ret) {
            m_current = position(i)->next;
            m_step = step;
        }
    }

    // 右边是否达到尾部(是否为空)
    bool end()
    {
        return (m_current == NULL);
    }


    // 获取游标所指向的数据元素
    T current()
    {
        if (!end()) {
            return m_current->value;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position");
        }
    }

    // 移动游标
    bool next()
    {
        int i = 0;
        while((i < m_step) && !end()) {
            m_current = m_current->next;
            i++;
        }

        return (i == m_step);
    }



    ~LinkList()
    {
        clear();
    }


};



}


#endif
