#ifndef CIRCLE_LIST_H
#define CIRCLE_LIST_H

#include "link_list.h"

namespace DTLib {



template <typename T>
class CircleList : public LinkList<T> {
protected:
    typedef typename LinkList<T>::Node Node;

    int mod(int i) const // O(1)
    {
        return (this->m_length == 0) ? 0 : (i % this->m_length);
    }

    Node *last() const // O(n)
    {
        return this->position(this->m_length - 1)->next;
    }

    void last_to_first() const // O(n)
    {
        last()->next  =this->m_header.next;
    }

public:
    bool insert(const T &e) // O(n)
    {
        return insert(this->m_length, e);
    }

    bool insert(int i, const T &e) // O(n)
    {
        bool ret = true;


        i = i % (this->m_length + 1);

        ret = LinkList<T>::insert(i, e);

        if (ret && (i == 0)) {
            last_to_first();
        }

        return ret;
    }

    bool remove(int i) { // O(n)
        bool ret = true;

        i = mod(i);

        if (i == 0) {
            Node *toDel = this->m_header.next;
            if (toDel != NULL) {
                this->m_header.next = toDel->next;
                this->m_length--;
                if (this->m_length > 0) {
                    last_to_first(); // O(n)
                    if (this->m_current == toDel) {
                        this->m_current = toDel->next;
                    }
                } else {
                    this->m_header.next = NULL;
                    this->m_current = NULL;
                }

                this->destroy(toDel);
            } else {
                ret = false;
            }
        } else {  //非首节点的情形
            ret = LinkList<T>::remove(i); // O(n)
        }
        return ret;
    }

    bool set (int i, const T &e) // O(n)
    {
        return LinkList<T>::set(mod(i), e);
    }

    T get(int i) const // O(n)
    {
        return LinkList<T>::get(mod(i));
    }

    bool get(int i, const T &e) const // O(n)
    {
        return LinkList<T>::get(mod(i), e);
    }

    int find(const T &e) const // O(n)
    {
        int ret = -1;
        Node *slider = this->m_header.next;
        for(int i = 0; i < this->m_length; i++) {
            if (slider->value == e) {
                ret = i;
                break;
            }
            slider = slider->next;
        }
        return ret;
    }

    void clear() // O(n)
    {
        while(this->m_length > 1) { // O(n)
            remove(1); // remove(1)而不是remove(0)是为了效率 // O(1)
        }
        if (this->m_length == 1) { // 首节点特殊处理 // O(1)
            Node *toDel = this->m_header.next;
            this->m_header.next = NULL;
            this->m_length = 0;
            this->m_current = NULL;

            this->destroy(toDel);
        }
    }

    // 将游标定位到目标位置
    bool move(int i, int step = 1) // O(n)
    {
        return LinkList<T>::move(mod(i), step);
    }

    // 右边是否达到尾部(是否为空)
    bool end() // O(1)
    {
        return (this->m_length == 0) || (this->m_current == NULL); // 循环链表永远不会end
        //return (this->m_length == 0) || (this->m_current->next == this->m_header.next);
    }
    ~CircleList() // O(n)
    {
        clear();
    }
};

}

#endif
