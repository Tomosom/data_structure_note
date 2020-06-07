/*
 * 基本思想：
 *  - 用一维数组存储顶点：描述顶点相关的数据
 *  - 用二维数组存储边：描述顶点间的关系和权
 */

#ifndef GRAPH_H
#define GRAPH_H

#include "object.h"
#include "shared_pointer.h"
#include "array.h"
#include "dynamic_array.h"
#include "link_queue.h"
#include "link_stack.h"
#include "sort.h"

namespace DTLib {

// 边相关的数据类型
template <typename E>
struct Edge : public Object {
    int b;  // 起点 begin vertex
    int e;  // 终点 end vertex
    E data; // 权值

    Edge(int i = -1, int j = -1)
    {
        b = i;
        e = j;
    }

    Edge(int i, int j, const E &value)
    {
        b = i;
        e = j;
        data = value;
    }

    bool operator == (const Edge<E> &obj)
    {
        return (b == obj.b) && (e == obj.e);
    }

    bool operator != (const Edge<E> &obj)
    {
        return !(*this == obj);
    }

    bool operator < (const Edge<E> &obj)
    {
        return (data < obj.data);
    }
    bool operator > (const Edge<E> &obj)
    {
        return (data > obj.data);
    }
};

template <typename V, typename E>
class Graph : public Object {
protected:
    template <typename T>
    DynamicArray<T> *toArray(LinkQueue<T> &queue)
    {
        DynamicArray<T> *ret = new DynamicArray<T>(queue.length());
        if (ret != NULL) {
            for (int i = 0; i < ret->length(); i++, queue.remove()) {
                ret->set(i, queue.front());
            }
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create ret object ...");
        }

        return ret;
    }

    // 拿到图中所有的边
    SharedPointer< Array< Edge<E> > > getUndirectedEdges()
    {
        DynamicArray< Edge<E> > *ret = NULL;

        if (asUndirected()) {
            LinkQueue< Edge<E> > queue;

            for (int i = 0; i < vCount(); i++) {
                for (int j = i; j < vCount(); j++) {
                    if (isAdjacent(i, j)) {
                        queue.add(Edge<E>(i, j, getEdge(i, j)));
                    }
                }
            }

            ret = toArray(queue);
        } else {
            THROW_EXCEPTION(InvalidParameterException, "This function is for undirected graph only ...");
        }
        return ret;
    }

    int find(Array<int> &p, int v)
    {
        while(p[v] != -1) {
            v = p[v];
        }
        return v;
    }

public:
    /* 获取顶点相关的数据元素值 */
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V &value) = 0;
    /* 设置顶点相关的数据元素值 */
    virtual bool setVertex(int i, const V &value) = 0;
    /* 获取邻接顶点 */
    virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;

    /* 判断在当前图中顶点i到顶点j是否邻接 */
    virtual bool isAdjacent(int i, int j) = 0;

    /* 获取边相关的数据元素值 */
    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E &value) = 0;
    /* 设置边相关的数据元素值 */
    virtual bool setEdge(int i, int j, const E &value) = 0;
    /* 删除边 */
    virtual bool removeEdge(int i, int j) = 0;
    /* 获取定点数 */
    virtual int vCount() = 0;
    /* 获取边数 */
    virtual int eCount() = 0;
    /* 获取出度 */
    virtual int OD(int i) = 0;
    /* 获取入度 */
    virtual int ID(int i) = 0;
    /* 获取总的度 */
    virtual int TD(int i)
    {
        return OD(i) + ID(i);
    }

    /* 判断当前的有向图是否能够看做无向图 */
    bool asUndirected()
    {
        bool ret = true;
        for (int i = 0; i < vCount(); i++) {
            for (int j = 0; j < vCount(); j++) {
                if (isAdjacent(i, j)) {
                    ret = ret && isAdjacent(j, i) && (getEdge(i, j) == getEdge(j, i));
                }
            }
        }
        return ret;
    }

    /* 
     * 最小生成树定义
     *  - 仅适用图中的 n - 1 条边连接图中的 n 个顶点
     *  - 不能使用产生回路的边
     *  - 各边上的权值的总和达到最小
     * 
     * Prim 算法概览
     * 普里姆算法（Prim算法），图论中的一种算法，可在加权连通图里搜索最小生成树。
     * 意即由此算法搜索到的边子集所构成的树中，不但包括了连通图里的所有顶点(英
     * 语：Vertex (graph theory))，且其所有边的权值之和亦为最小。该算法于1930年
     * 由捷克数学家沃伊捷赫·亚尔尼克（英语：Vojtěch Jarník）发现；并在1957年由
     * 美国计算机科学家罗伯特·普里姆（英语：Robert C. Prim）独立发现；1959年，
     * 艾兹格·迪科斯彻再次发现了该算法。因此，在某些场合，普里姆算法又被称为DJP算法、
     * 亚尔尼克算法或普里姆－亚尔尼克算法。
     * 
     * prim 算法步骤(通过顶点的动态标记)
     *  1. 选择某一顶点V0作为起始顶点, 使得 T = { v0 }, F = { v1,v2,v3,...vn }, E = { }
     *  2. 每次选择一条边,这条边是所有(u, v)中权值最小的边,且 u∈T, v∈F
     *  3. 修改T, F, E
     *          T = T + { v }, F = F - { v }, E = E + { (U, V) }
     *  4. 当 F != NULL 时, 且(u, v)存在, 转2; 否则, 结束
     */
    SharedPointer< Array< Edge<E> > > prim(const E &LIMIT, const bool MINIMUM = true)
    {
        LinkQueue< Edge<E> > ret;
        if (asUndirected()) {
            DynamicArray<int> adjVex(vCount());
            DynamicArray<bool> mark(vCount());
            DynamicArray<E> cost(vCount());
            SharedPointer< Array<int> > aj = NULL; // 保存邻接顶点数组
            bool end = false; // flag
            int v = 0; // 习惯性地从0顶点开始寻找最小生成树

            for (int i = 0; i < vCount(); i++) {
                adjVex[i] = -1;
                mark[i] = false;
                cost[i] = LIMIT; // 理论上的最大权值
            }

            mark[v] = true;

            aj = getAdjacent(v);

            for (int j = 0; j < aj->length(); j++) {
                cost[(*aj)[j]] = getEdge(v, (*aj)[j]);
                adjVex[(*aj)[j]] = v;
            }

            for (int i = 0; (i < vCount()) && !end; i++) {
                E m = LIMIT;
                int k = -1;

                for (int j = 0; j < vCount(); j++) {
                    if (!mark[j] && (MINIMUM ? (cost[j] < m) : (cost[j] > m))) {
                        m = cost[j];
                        k = j;
                    }
                }

                end = (k == -1);

                if ( !end ) {
                    ret.add(Edge<E>(adjVex[k], k, getEdge(adjVex[k], k)));

                    mark[k] = true;
                    aj = getAdjacent(k);
                    for (int j = 0;j < aj->length(); j++) {
                        if ( !mark[(*aj)[j]] &&
                             (MINIMUM ? (getEdge(k, (*aj)[j]) < cost[(*aj)[j]]) :
                                        (getEdge(k, (*aj)[j]) > cost[(*aj)[j]])) ) {
                            cost[(*aj)[j]] = getEdge(k, (*aj)[j]);
                            adjVex[(*aj)[j]] = k;
                        }
                    }
                }
            }

        } else {
            THROW_EXCEPTION(IndexOutOfBoundsException, "Prim operation is for undirected graph only ...");
        }

        if (ret.length() != (vCount() - 1)) {
            THROW_EXCEPTION(IndexOutOfBoundsException, "No enough edges for prim operation ...");
        }

        return toArray(ret);
    }

    /* 
     * 最小生成树定义
     *  - 仅适用图中的 n - 1 条边连接图中的 n 个顶点
     *  - 不能使用产生回路的边
     *  - 各边上的权值的总和达到最小
     * 
     * Kruskal 算法概览
     * Kruskal算法是一种用来寻找最小生成树的算法，由Joseph Kruskal在1956年发表。
     * 用来解决同样问题的还有Prim算法和Boruvka算法等。三种算法都是贪婪算法的应用。
     * 和Boruvka算法不同的地方是，Kruskal算法在图中存在相同权值的边时也有效。
     * 
     * 需解决的问题 : 如何判断新选择的边与已选择的边是否构成回路
     * 技巧:前驱标记数组
     *  - 定义数组:Array<int> p(vCount());
     *  - 数组元素的意义:
     *      p[n] 标识顶点 n 在边的连接通路上的另一端顶点
     * 
     * Kruskal 算法步骤(以边为核心)
     *  1. 定义前驱标记数组: Array<int> p(vCount());
     *  2. 获取当前图中的所有边,并存储于edges数组中
     *  3. 对数组edges按照权值进行排序
     *  4. 利用 p 数组在edges数组中选择前 n-1 不构成回路的边 
     */
    SharedPointer< Array< Edge<E> > > Kruskal(const bool MINIMUM = true)
    {
        LinkQueue< Edge<E> > ret;
        SharedPointer< Array< Edge<E> > > edges = getUndirectedEdges();
        DynamicArray<int> p(vCount());
        for (int i = 0; i < p.length(); i++) {
            p[i] = -1;
        }

        Sort::Shell_from_insert(*edges, MINIMUM);

        for(int i = 0; (i < edges->length()) && (ret.length() < (vCount() - 1)); i++) {
            int b = find(p, (*edges)[i].b);
            int e = find(p, (*edges)[i].e);

            if (b != e) {
                p[e] = b;
                ret.add((*edges)[i]);
            }
        }

        if (ret.length() != (vCount() - 1)) {
            THROW_EXCEPTION(InvalidOperationException, "No enough edges for Kruskal operation ...");
        }

        return toArray(ret);
    }

    /*
     * 图遍历
     * BFS : Breadth First Search 广度优先遍历
     *  以二叉树层次遍历的思想对图进行遍历
     * 
     * 广度优先算法
     *  - 原料 : class LinkQueue<T>;
     *  - 步骤 :
     *      1. 将其实定点压入队列中
     *      2. 队头顶点 v 弹出, 判断是否已经标记 (标记 : 转2, 未标记 : 转3)
     *      3. 标记顶点 v, 并将顶点v的邻接顶点压入队列中
     *      4. 判断队列是否为空 (非空 : 转2, 空 : 结束)
     */
    SharedPointer< Array<int> > BFS(int i)
    {
        DynamicArray<int> *ret = NULL;

        if ( (0 <= i) && (i <= vCount()) ) {
            LinkQueue<int> q;
            LinkQueue<int> r;   //  return 队列
            DynamicArray<bool> visited(vCount());

            for(int j = 0; j < visited.length(); j++) {
                visited[j] = false;
            }

            q.add(i);

            while(q.length() > 0) {
                int v = q.front();
                q.remove();

                if (!visited[v]) {
                    SharedPointer< Array<int> > aj = getAdjacent(v);

                    for(int j = 0; j < aj->length(); j++) {
                        q.add((*aj)[j]);
                    }

                    r.add(v);
                    visited[v] = true;
                }
            }

            ret = toArray(r);
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
        }

        return ret;
    }

    /*
     * 图遍历
     * DFS : Depth First Search 深度优先遍历
     * 
     * 深度优先算法
     *  - 原料 : class LinkStack<T>;
     *  - 步骤 : 
     *      1. 将起始顶点压入栈中
     *      2. 弹出栈顶顶点v, 判断是否已经标记( 标记 : 转2, 未标记 : 转3 )
     *      3. 标记顶点v, 并将顶点v的邻接顶点压入栈中
     *      4. 判断栈是否为空 ( 非空 : 转2, 空 : 结束 )
     */
    SharedPointer< Array<int> > DFS(int i)
    {
        DynamicArray<int> *ret = NULL;

        if ( (0 <= i) && (i <= vCount()) ) {
            LinkStack<int> s;
            LinkQueue<int> r; // return 队列
            DynamicArray<bool> visited(vCount());

            for (int j = 0; j < visited.length(); j++) {
                visited[j] = false;
            }

            s.push(i);

            while(s.size() > 0) {
                int v = s.top();
                s.pop();
                if (!visited[v]) {
                    SharedPointer< Array<int> > aj = getAdjacent(v);
                    for(int j = aj->length() - 1; j >= 0; j--) {
                        s.push((*aj)[j]);
                    }

                    r.add(v);
                    visited[v] = true;
                }
            }

            ret = toArray(r);

        } else {
            THROW_EXCEPTION(InvalidParameterException, "index i is invalid ...");
        }

        return ret;
    }

    /*
     * 最短路径
     * Dijkstras算法概述
     * 迪杰斯特拉算法(Dijkstra)是由荷兰计算机科学家狄克斯特拉于1959 年提出的，
     * 因此又叫狄克斯特拉算法。是从一个顶点到其余各顶点的最短路径算法，解决的
     * 是有权图中最短路径问题。迪杰斯特拉算法主要特点是以起始点为中心向外层层
     * 扩展，直到扩展到终点为止。
     * 
     * Dijkstras算法步骤 ( 基于递推思想完成的 )
     * 1. 初始化: S ← { v0 }
     *      dist[j] ← Edge[0][j], j = 1, 2, ..., n - 1;
     * 2. 找出最小路径值所对应的顶点K;
     *      dist[k] == min { dist[i] }, i ∈ V - S;
     *      S ← S U { K };  // 标记k顶点进入 S 集合
     * 3. 对于每一个 i ∈ V - S 修改:
     *      dist[i] ← min { dist[i], dist[k] + Edge[k][i] }
     * 4. 判断: 若 S == V , 则算法结束,否则转2
     */
    SharedPointer< Array<int> > dijkstra(int i, int j, const E &LIMIT)
    {
        LinkQueue<int> ret;

        if ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount())) {
            DynamicArray<E> dist(vCount());
            DynamicArray<int> path(vCount());
            DynamicArray<bool> mark(vCount());

            for (int k = 0; k < vCount(); k++) {
                mark[k] = false;
                path[k] = -1;

                dist[k] = isAdjacent(i, k) ? (path[k] = i, getEdge(i, k)) : LIMIT;
            }

            mark[i] = true;

            for(int k = 0; k < vCount(); k++) {
                E m = LIMIT;
                int u = -1;

                for (int w = 0; w < vCount(); w++) {
                    if (!mark[w] && (dist[w] < m)) {
                        m = dist[w];
                        u = w;
                    }
                }

                if (u == -1) {
                    break;
                }

                mark[u] = true;

                for (int w = 0; w < vCount(); w++) {
                    if ( !mark[w] && isAdjacent(u, w) && (dist[u] + getEdge(u, w) < dist[w]) ) {
                        dist[w] = dist[u] + getEdge(u, w);
                        path[w] = u;
                    }
                }
            }

            LinkStack<int> s;
            s.push(j);
            for (int k = path[j]; k != -1; k = path[k]) {
                s.push(k);
            }

            while(s.size() > 0) {
                ret.add(s.top());
                s.pop();
            }

        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index <i, j> is invalid ...");
        }

        if(ret.length() < 2) {
            THROW_EXCEPTION(ArithmetricException, "There is no path from i to j ...");
        }

        return toArray(ret);
    }

    /*
     * 最短路径
     * Floyd算法概述 ( https://baike.baidu.com/item/Floyd算法/291990 )
     * Floyd算法又称为插点法，是一种利用动态规划的思想寻找给定的加权图中多源点之间最
     * 短路径的算法，与Dijkstra算法类似。该算法名称以创始人之一、1978年图灵奖获得者、
     * 斯坦福大学计算机科学系教授罗伯特·弗洛伊德命名。
     * 
     * Floyd算法核心
     *  - 定义一个n阶方阵序列:
     *      A(-1), A(0), ..., A(n-1)
     *  - 其中:
     *      A(-1)[i][j] = Edge[i][j]    //邻接矩阵
     *      A(k)[i][j] = min { A(k-1)[i][j], A(k-1)[i][k] + A(k-1)[k][j] }  , k = 0, 1, ..., n-1 
     * 
     * Floyd算法说明
     *  - A(-1)定义为邻接矩阵, 则:
     *      A(0), ..., A(n-1) 通过中转顶点逐一递推得到
     *  - A(k)矩阵中元素的更新:
     *      A(k)[i][j] = min { A(k-1)[i][j], A(k-1)[i][k] + A(k-1)[k][j] }
     *  - A矩阵的推导就是最短路径的推导
     *      A[i][j]为i到j额路径值, 在推导过程中逐步减小
     * 
     * 问题点 : 如何记录最短路径上的各个顶点?
     *  定义辅助矩阵:
     *  - int path[N][N];   // 路径矩阵
     *      - path[i][j]标识i到j的路径上所经过的第1个顶点
     *      - 初始化:path[i][j] = -1(无直接的边连接); or path[i][j] = j;(有直接的边连接,直接为终点)
     *      - 修改:
     *          if ( (dist[i][k] + dist[k][j]) < dist[i][j] ) {
     *              dist[i][j] = dist[i][k] + dist[k][j];
     *              path[i][j] = path[i][k];    // 新增
     *          }
     */

#if 0
    // 仅能返回最短路径值,不能返回最短路径
    int floyd(int x, int y, const E &LIMIT)
    {
        int ret = -1;

        if ( (0 <= x) && (x < vCount()) && (0 <= y) && (y < vCount()) ) {
            DynamicArray< DynamicArray<E> > dist(vCount()); // 定义二维数组

            for (int k = 0; k < vCount(); k++) {
                dist[k].resize(vCount());
            }

            // 创建A(-1)方阵
            for (int i = 0; i < vCount(); i++) {
                for (int j = 0; j < vCount(); j++) {
                    dist[i][j] =  isAdjacent(i, j) ? getEdge(i, j) : LIMIT;
                }
            }

            for (int k = 0; k < vCount(); k++) {
                for (int i = 0; i < vCount(); i++) {
                    for (int j = 0; j < vCount(); j++) {
                        if ( (dist[i][k] + dist[k][j]) < dist[i][j] ) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                        }
                    }
                }
            }

            ret = dist[x][y];
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index <i, j> is invalid ...");
        }

        return ret;
    }
#else
    // 可返回路径
    SharedPointer< Array<int> > floyd(int x, int y, const E &LIMIT)
    {
        LinkQueue<int> ret;

        if ( (0 <= x) && (x < vCount()) && (0 <= y) && (y < vCount()) ) {
            DynamicArray< DynamicArray<E> > dist(vCount()); // 定义二维数组
            DynamicArray< DynamicArray<int> > path(vCount());

            for (int k = 0; k < vCount(); k++) {
                dist[k].resize(vCount());
                path[k].resize(vCount());
            }

            // 创建A(-1)方阵
            for (int i = 0; i < vCount(); i++) {
                for (int j = 0; j < vCount(); j++) {
                    path[i][j] = -1;
                    dist[i][j] =  isAdjacent(i, j) ? (path[i][j] = j, getEdge(i, j)) : LIMIT; // 逗号表达式可提高效率
                }
            }

            for (int k = 0; k < vCount(); k++) {
                for (int i = 0; i < vCount(); i++) {
                    for (int j = 0; j < vCount(); j++) {
                        if ( (dist[i][k] + dist[k][j]) < dist[i][j] ) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            path[i][j] = path[i][k];
                        }
                    }
                }
            }

            while((x != -1) && (x != y)) {
                ret.add(x);
                x = path[x][y];
            }

            if (x != -1) {
                ret.add(x);
            }

        } else {
            THROW_EXCEPTION(InvalidParameterException, "Index <i, j> is invalid ...");
        }

        if(ret.length() < 2) {
            THROW_EXCEPTION(ArithmetricException, "There is no path from i to j ...");
        }

        return toArray(ret);
    }
#endif
};

}

#endif
