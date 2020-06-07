#include <iostream>
#include "matrix_graph.h"
#include "list_graph.h"

using namespace std;
using namespace DTLib;

/*
 * 不下降序列问题:
 * 设由 n 个数组成的数列, 记为: a[1], a[2], ..., a[n], 若存在 i1 < i2 < ... < im 满足
 * a[i1] <= a[i2] <= ... <= a[im], 则称为程度为 m 的不下降序列.
 * 
 * 最长不下降序列问题建模:
 *  - 使用数列中的元素和元素间的关系建立图模型
 *      - 图中顶点的附加数据值为对应的数列元素值
 *      - 图中的边按照如下方式建立
 *          当数列中的某个元素与后续元素存在不下降关系时
 *          从该元素对应的顶点到后续元素对应的顶点存在一条有向边
 *          边的权值固定为 1
 * 
 * 解决思路:
 * - 以每一个顶点作为起始顶点寻找局部最多顶点路径
 *      v0 -> p0, v1 -> p1, ... , v(n-1) -> p(n-1)
 * - 寻找全局最多顶点的路径
 *      pm = max{ p0, p1, ... , p(n-1) } 
 * 
 * 局部最多顶点路径求解思路: (递归思路)
 * - 获取当前顶点 v 的邻接顶点 { aj0, aj1, ... }
 * - 以各个邻接顶点为起点求解最多顶点路径 { p(aj0), p(aj1), ... }
 * - pv = max{ p(aj0), p(aj1), ... } + 1
 * 
 */
/*
 * 原材料
 * - 以 v 作为起始顶点寻找图 g 中最多顶点路径
 * - Array<int> count;
 *      count[i] 表示以 i 起始的最多顶点路径上的顶点数
 * - Array<int> path;
 *      path[i] 表示以 i 起始的最多顶点路径上经过的第一个顶点
 * - Array<bool> mark;
 *      如果 i 起始的最多顶点路径已找到, 则: mark[i] 为 true
 */
int search_max_path(Graph<int, int> &g, int v, Array<int> &count, 
    Array< LinkList<int>* > &path, Array<bool> &mark)
{
    int ret = 0;
    //int k = -1;
    SharedPointer< Array<int> > aj = g.getAdjacent(v);

    for (int i = 0; i < aj->length(); i++) {
        int num = 0;

        if ( !mark[(*aj)[i]] ) {
            num = search_max_path(g, (*aj)[i], count, path, mark);
        } else {
            num = count[(*aj)[i]];
        }

        if (ret < num) {
            ret = num;
            //k = (*aj)[i];
        }
    }

    for (int i = 0; i < aj->length(); i++) {
        if (ret == count[(*aj)[i]]) {
            path[v]->insert((*aj)[i]);
        }
    }

    ret++;

    count[v] = ret;
    mark[v] = true;
    //path[v] = k;

    return ret;
}

SharedPointer< Graph<int, int> > create_graph(int *a, int len)
{
    ListGraph<int, int> *ret = new ListGraph<int, int>(len);

    for (int i = 0; i < len; i++) {
        ret->setVertex(i, a[i]);
    }

    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (a[i] <= a[j]) {
                ret->setEdge(i, j, 1);
            }
        }
    }

    return ret;
}

void init_array(Array<int> &count, Array< LinkList<int>* > &path, Array<bool> &mark)
{
    for (int i = 0; i < count.length(); i++) {
        count[i] = 0;
    }

    for (int i = 0; i < path.length(); i++) {
        path[i] = new LinkList<int>();
    }

    for (int i = 0; i < mark.length(); i++) {
        mark[i] = false;
    }
}

void print_path(Graph<int, int> &g, int v, Array< LinkList<int>* > &path, LinkList<int> &cp)
{
    cp.insert(v);

    if (path[v]->length() > 0) {
        for (path[v]->move(0); !path[v]->end(); path[v]->next()) {
            print_path(g, path[v]->current(), path, cp);
        }
    } else {
        cout << "Element: ";
        for (cp.move(0); !cp.end(); cp.next()) {
            cout << g.getVertex(cp.current()) << " ";
        }
        cout << endl;
    }

    cp.remove(cp.length() - 1);
}

void print_max_path(Graph<int, int> &g, Array<int> &count, Array< LinkList<int>* > &path)
{
    int max = 0;
    LinkList<int> cp;

    for (int i = 0; i < count.length(); i++) {
        if (max < count[i]) {
            max = count[i];
        }
    }

    cout << "Len: " << max << endl;
    for (int i = 0; i < count.length(); i++) {
        if (max == count[i]) {
            print_path(g, i, path, cp);
        }
    }
}

void search_max_path(Graph<int, int> &g, Array<int> &count, 
    Array< LinkList<int>* > &path, Array<bool> &mark)
{
    for (int i = 0; i < g.vCount(); i++) {
        if ( !mark[i] ) {
            search_max_path(g, i, count, path, mark);
        }
    }
}

void solution(int *a, int len)
{
    DynamicArray<int> count(len);
    DynamicArray< LinkList<int>* > path(len);
    DynamicArray<bool> mark(len);
    SharedPointer< Graph<int, int> >g;

    g = create_graph(a, len);

    init_array(count, path, mark);

    search_max_path(*g, count, path, mark);

    print_max_path(*g, count, path);
}


int main(int argc, char **argv)
{
    int a[] = { 3, 18, 7, 14, 10, 12, 23, 41, 16, 24 }; // 关键测试点,是否能找到所有最长不下降序列
    //int a[] = { 1, 3, 4, 2, 5 };
    //int a[] = { 10, 30, 50, 1, 3, 5 };
    //int a[] = { 5, 3, 2, 1 };
    //int a[] = { 1, 2, 3, 4, 5 };
    //int a[] = { 1, 3, 5, 4 };   // 关键测试点,是否能找到所有最长不下降序列
    //int a[] = { 2, 1, 3, 5, 4 };   // 关键测试点,是否能找到所有最长不下降序列

    solution(a, sizeof(a)/sizeof(*a));

    return 0;	
}