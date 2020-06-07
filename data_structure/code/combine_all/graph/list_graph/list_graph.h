/*
 * 基本思想：
 *  根据邻接矩阵法中的残留问题，
 *  为了进一步提高空间使用率，可以考虑使用链表替换数组，将邻接矩阵变换为邻接链表。。
 * 
 * 邻接链表法：
 *  - 图中的所有顶点按照编号存储于同一个链表中
 *  - 每一个顶点对应一个链表，用于存储始发与该顶点的边
 *  - 每一条边的信息包含：起点，终点，权值
 */
#ifndef LIST_GRAPH_H
#define LIST_GRAPH_H

#include "graph.h"
#include "link_list.h"
#include "exception.h"
#include "dynamic_array.h"


namespace DTLib {

template <typename V, typename E> 
class ListGraph : public Graph<V, E> {

    // 顶点相关的数据类型
    struct Vertex : public Object{
        V *data;
        LinkList< Edge<E> > edge;

        Vertex()
        {
            data = NULL;
        }
    };

    // 定义实际的邻接链表
    LinkList<Vertex*> m_list;

public:
    ListGraph(unsigned int n = 0)
    {
        for (unsigned int i = 0; i < n; i++) {
            addVertex();
        }
    }

    int addVertex()   // O(n)
    {
        int ret = -1;
        Vertex *v = new Vertex;
        if (v != NULL) {
            m_list.insert(v);   // O(n)
            ret = m_list.length() - 1; // 插入节点的编号
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new vertex object ...");
        }

        return ret;
    }

    int addVertex(const V &value)   // O(n)
    {
        int ret = addVertex();
        if (ret >= 0) {
            setVertex(ret, value);
        }

        return ret;
    }

    bool setVertex(int i, const V &value)   // O(n)
    {
        int ret = ((0 <= i) && (i <= vCount()));
        if (ret) {
            Vertex *vertex = m_list.get(i);   // O(n)
            V *data = vertex->data;

            if (data == NULL) {
                data = new V();
            }

            if (data != NULL) {
                *data = value;
                vertex->data = data;
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new vertex value ...");
            }
        }

        return ret;
    }

    V getVertex(int i)   // O(n)
    {
        V ret;
        if (!getVertex(i, ret)) {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }
        return ret;
    }

    bool getVertex(int i, V &value)   // O(n)
    {
        int ret = ((0 <= i) && (i <= vCount()));
        if (ret) {
            Vertex *v = m_list.get(i);
            if (v->data != NULL) {
                value = *(v->data);
            } else {
                THROW_EXCEPTION(InvalidParameterException, "No value assigned to this vertex ...");
            }
        }

        return ret;
    }
    /* 删除最近添加的顶点 */
    void removeVertex()   // O(n2)
    {
        if (m_list.length() > 0) {
            int index = m_list.length() - 1;
            Vertex *v = m_list.get(index);   // O(n)
            if (m_list.remove(index)) {
                // 其他邻接顶点有无相关的边
                for (int i = (m_list.move(0), 0); !m_list.end(); i++, m_list.next()) {   // O(n)
                    int pos = m_list.current()->edge.find(Edge<E>(i, index));   // O(n)
                    if (pos >= 0) {
                        m_list.current()->edge.remove(pos);
                    }
                }
                delete v->data;
                delete v;
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "No vertex in current graph ...");
        }
    }

    /* 获取邻接顶点 */
    SharedPointer< Array<int> > getAdjacent(int i)   // O(n)
    {
        DynamicArray<int> *ret = NULL;
        if ( (0 <= i) && (i < vCount()) ) {
            Vertex *vertex = m_list.get(i);   // O(n)
            ret = new DynamicArray<int>(vertex->edge.length());
            if (ret != NULL) {
                for (int k = (vertex->edge.move(0), 0); !vertex->edge.end(); k++, vertex->edge.next()) {
                    ret->set(k, vertex->edge.current().e);   
                }
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object ...");
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ... ");
        }

        return ret;
    }

    /* 判断在当前图中顶点i到顶点j是否邻接 */
    bool isAdjacent(int i, int j)
    {
        return (0 <= i) && (i < vCount()) &&
               (0 <= j) && (j < vCount()) && 
               (m_list.get(i)->edge.find(Edge<E>(i, j)) >= 0); // 对应的边是否存在
    }

    /* 获取边 */
    E getEdge(int i, int j)   // O(n)
    {
        E ret;
        if (!getEdge(i, j, ret)) {
            THROW_EXCEPTION(InvalidParameterException, "Edge <i, j> is invalid ...");
        }
        return ret;
    }

    bool getEdge(int i, int j, E &value)   // O(n)
    {
        int ret = ( (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()) );
        if (ret) {
            Vertex *vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i, j));
            if (pos >= 0) {
                value = vertex->edge.get(pos).data;
            } else {
                THROW_EXCEPTION(InvalidParameterException, "No value assigned to this edge ...");
            }
        }

        return ret;
    }

    /* 设置边 */
    bool setEdge(int i, int j, const E &value)   // O(n)
    {
        int ret = ( (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()) );
        if (ret) {
            Vertex *vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i, j));
            if (pos >= 0) {
                ret = vertex->edge.set(pos, Edge<E>(i, j, value));
            } else {
                ret = vertex->edge.insert(0, Edge<E>(i, j, value));
            }
        }

        return ret;
    }

    /* 删除边 */
    bool removeEdge(int i, int j)   // O(n)
    {
        int ret = ( (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()) );
        if (ret) {
            Vertex *vertex = m_list.get(i);
            int pos = vertex->edge.find(Edge<E>(i, j));
            if (pos >= 0) {
                ret = vertex->edge.remove(pos);
            }
        }

        return ret;
    }

    /* 获取顶点数 */
    int vCount()   // O(1)
    {
        return m_list.length();
    }


    /* 获取边数 */
    int eCount()   // O(n)
    {
        int ret = 0;

        for (m_list.move(0); !m_list.end(); m_list.next()) {
            ret += m_list.current()->edge.length();
        }
        return ret;
    }
    /* 获取出度 */
    int OD(int i)   // O(n)
    {
        int ret = 0;

        if ( (0 <= i) && (i <= vCount()) ) {
            ret = m_list.get(i)->edge.length();   // O(n)
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }
    /* 获取入度 */
    int ID(int i)   // O(n2)
    {
        int ret = 0;

        if ( (0 <= i) && (i <= vCount()) ) {
            for (m_list.move(0); !m_list.end(); m_list.next()) {
                LinkList< Edge<E> > &edge = m_list.current()->edge;
                for (edge.move(0); !edge.end(); edge.next()) {
                    if (edge.current().e == i) {
                        ret++;
                        break;
                    }
                }
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    ~ListGraph()
    {
        while(m_list.length() > 0) {
            Vertex *toDel = m_list.get(0);
            m_list.remove(0);
            delete toDel->data;
            delete toDel;
        }
    }


};



}



#endif
