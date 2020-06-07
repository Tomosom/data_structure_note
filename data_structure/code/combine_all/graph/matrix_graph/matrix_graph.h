/*
 * 基本思想：
 *  - 用一维数组存储顶点：描述顶点相关的数据
 *  - 用二维数组存储边：描述顶点间的关系和权
 *      邻接矩阵法：
 *          设图A = (V, E)是一个有n个顶点的图，图的邻接矩阵为Edge[n][n]，则：
 * 
 *                       | W, W权值, i 和 j 连接
 *          Edge[i][j] = |
 *                       | 空, i == j 或 i 和 j 不连接
 * 
 *      注：解决工程问题时，习惯于对图中的每个顶点进行编号，当不需要权值时，取 W 非空便是节点间有连接
 */

#ifndef MATRIX_GRAPH_H
#define MATRIX_GRAPH_H

#include "exception.h"
#include "graph.h"
#include "dynamic_array.h"

namespace DTLib {

/* 
 * N : 图中顶点的个数
 * V ：图中顶点的类型
 * E : 图中边的类型
 */
template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E> {
protected:

    /* 若下面定义，效率会是很大问题 */
    //V m_vertexes[N];    // 存储与顶点相关的数据元素
    //E m_edges[N][N];    // 邻接矩阵
    
    V *m_vertexes[N];    // 存储与顶点相关的数据元素
    E *m_edges[N][N];    // 邻接矩阵

    int m_eCount;        // 当前图中边的个数

public:
    MatrixGraph()
    {
        for(int i = 0; i < vCount(); i++) {
            m_vertexes[i] = NULL;
            for (int j = 0; j < vCount(); j++) {
                m_edges[i][j] = NULL;
            }
        }
        m_eCount = 0;
    }

    /* 获取顶点相关的数据元素值 */
    V getVertex(int i)  // O(1)
    {
        V ret;

        if (!getVertex(i, ret)) {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ... ");
        }

        return ret;
    }
    bool getVertex(int i, V &value) // O(1)
    {
        int ret = ((0 <= i) && (i < vCount()));
        if (ret) {
            if (m_vertexes[i] != NULL) {
                value = *(m_vertexes[i]);
            } else {
                THROW_EXCEPTION(InvalidParameterException, "No value assigned to this vertex ...");
            }
        }

        return ret;
    }
    /* 设置顶点相关的数据元素值 */
    bool setVertex(int i, const V &value)   // O(1)
    {
        bool ret = ( (0 <= i) && (i < vCount()) );
        if (ret) {
            V *data = m_vertexes[i]; // 使用中间变量实现异常安全，若不使用此中间变量，下面复制异常时，可能会有一个无效的节点
            if (data == NULL) {
                data = new V();
            }
            if (data != NULL) {
                *data = value;  // 此句可能发生异常，固定义上面中间变量
                m_vertexes[i] = data;
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new vertex value ...");
            }
        }

        return ret;
    }
    /* 获取邻接顶点(通过邻接矩阵中对应的行，获取邻接顶点的编号) */
    SharedPointer< Array<int> > getAdjacent(int i)  // O(n)
    {
        DynamicArray<int> *ret = NULL;
        if ( (0 <= i) && (i < vCount()) ) {
            int n = 0;
            for (int j = 0; j < vCount(); j++) {
                if (m_edges[i][j] != NULL) {
                    n++;
                }
            }

            ret = new DynamicArray<int>(n);
            if (ret != NULL) {
                for (int j = 0, k = 0; j < vCount(); j++) {
                    if (m_edges[i][j] != NULL) {
                        ret->set(k++, j);
                    }
                }
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object...");
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
               (m_edges[i][j] != NULL); // 邻接矩阵中是否有对应值
    }

    /* 获取边相关的数据元素值 */
    E getEdge(int i, int j) // O(1)
    {
        E ret;

        if (!getEdge(i, j, ret)) {
            THROW_EXCEPTION(InvalidParameterException, "Index <i, j> is invalid ...");
        }

        return ret;
    }
    bool getEdge(int i, int j, E &value)    // O(1)
    {
        int ret = ( (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()) );
        if (ret) {
            if (m_edges[i][j] != NULL) {
                value = *(m_edges[i][j]);
            } else {
                THROW_EXCEPTION(InvalidParameterException, "No value assigned to this edge ...");
            }
        }

        return ret;
    }
    /* 设置边相关的数据元素值 */
    bool setEdge(int i, int j, const E &value)  // O(1)
    {
        int ret = ( (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()) );
        if (ret) {
            E *ne = m_edges[i][j];  // 中间变量
            if (ne == NULL) {
                ne = new E();
                if (ne != NULL) {
                    *ne = value;
                    m_edges[i][j] = ne;
                    m_eCount++;
                } else {
                    THROW_EXCEPTION(NoEnoughMemoryException, "No memory to store new edge value ...");
                }
            } else {
                *ne = value;
            }
        }

        return ret;
    }
    /* 删除边 */
    bool removeEdge(int i, int j)   // O(1)
    {
        int ret = ( (0 <= i) && (i < vCount()) &&
                    (0 <= j) && (j < vCount()) );
        if (ret) {
            E *toDel = m_edges[i][j];
            m_edges[i][j] = NULL;
            if (toDel != NULL) {
                m_eCount--;
                delete toDel;
            }
        }

        return ret;
    }
    /* 获取定点数 */
    int vCount()       // O(1)
    {
        return N;
    }
    /* 获取边数 */
    int eCount()   // O(1)
    {
        return m_eCount;
    }
    /* 获取出度(矩阵中对应的行，有多少个不为空) */
    int OD(int i)   // O(n)
    {
        int ret = 0;

        if ( (0 <= i) && (i <= vCount()) ) {
            for (int j = 0; j < vCount(); j++) {
                if (m_edges[i][j] != NULL){
                    ret++;
                }
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }
    /* 获取入度(矩阵中对应的列，有多少个不为空) */
    int ID(int i)   // O(n)
    {
        int ret = 0;

        if ( (0 <= i) && (i <= vCount()) ) {
            for (int j = 0; j < vCount(); j++) {
                if (m_edges[j][i] != NULL){
                    ret++;
                }
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    ~MatrixGraph()
    {
        for(int i = 0; i < vCount(); i++) {
            for (int j = 0; j < vCount(); j++) {
                delete m_edges[i][j];
            }
            delete m_vertexes[i];
        }
    }
};

}

#endif