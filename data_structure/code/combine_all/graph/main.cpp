#include <iostream>
#include "matrix_graph.h"
#include "list_graph.h"

using namespace std;
using namespace DTLib;

#if 0
// 最小生成树测试

template <typename V, typename E>
Graph<V, E> &GraphEasy()
{
    static MatrixGraph<4, V, E> g;

    g.setEdge(0, 1, 1);
    g.setEdge(1, 0, 1);

    g.setEdge(0, 2, 3);
    g.setEdge(2, 0, 3);

    g.setEdge(1, 2, 1);
    g.setEdge(2, 1, 1);

    g.setEdge(1, 3, 4);
    g.setEdge(3, 1, 4);

    g.setEdge(2, 3, 1);
    g.setEdge(3, 2, 1);

    return g;
}

template< typename V, typename E >
Graph<V, E>& GraphComplex()
{
    static ListGraph<V, E> g(9);

    g.setEdge(0, 1, 10);
    g.setEdge(1, 0, 10);

    g.setEdge(0, 5, 11);
    g.setEdge(5, 0, 11);

    g.setEdge(1, 2, 18);
    g.setEdge(2, 1, 18);

    g.setEdge(1, 8, 12);
    g.setEdge(8, 1, 12);

    g.setEdge(1, 6, 16);
    g.setEdge(6, 1, 16);

    g.setEdge(2, 3, 22);
    g.setEdge(3, 2, 22);

    g.setEdge(2, 8, 8);
    g.setEdge(8, 2, 8);

    g.setEdge(3, 8, 21);
    g.setEdge(8, 3, 21);

    g.setEdge(3, 6, 24);
    g.setEdge(6, 3, 24);

    g.setEdge(3, 7, 16);
    g.setEdge(7, 3, 16);

    g.setEdge(3, 4, 20);
    g.setEdge(4, 3, 20);

    g.setEdge(4, 5, 26);
    g.setEdge(5, 4, 26);

    g.setEdge(4, 7, 7);
    g.setEdge(7, 4, 7);

    g.setEdge(5, 6, 17);
    g.setEdge(6, 5, 17);

    g.setEdge(6, 7, 19);
    g.setEdge(7, 6, 19);

    return g;
}

int main(int argc, char **argv)
{
    Graph<int, int> &g = GraphComplex<int, int>();
    //Graph<int, int> &g = GraphEasy<int, int>();

    //SharedPointer< Array< Edge<int> > > sa = g.prim(0, false);
    //SharedPointer< Array< Edge<int> > > sa = g.prim(65536);
    //SharedPointer< Array< Edge<int> > > sa = g.Kruskal();
    SharedPointer< Array< Edge<int> > > sa = g.Kruskal(false);
    int w = 0;

    for(int i=0; i<sa->length(); i++)
    {
        w += (*sa)[i].data;

        cout << (*sa)[i].b << " " << (*sa)[i].e << " " << (*sa)[i].data << endl;
    }

    cout << "Weight: " << w << endl;

    return 0;
}
#endif

#if 1

// 最短路径测试

template< typename V, typename E >
Graph<V, E>& GraphEasy()
{
    static MatrixGraph<4, V, E> g;

    g.setEdge(0, 1, 1);
    g.setEdge(0, 2, 3);
    g.setEdge(1, 2, 1);
    g.setEdge(1, 3, 4);
    g.setEdge(2, 3, 1);

    return g;
}

template< typename V, typename E >
Graph<V, E>& GraphComplex()
{
    static ListGraph<V, E> g(5);

    g.setEdge(0, 1, 10);
    g.setEdge(0, 3, 30);
    g.setEdge(0, 4, 100);

    g.setEdge(1, 2, 50);

    g.setEdge(2, 4, 10);

    g.setEdge(3, 2, 20);
    g.setEdge(3, 4, 60);

    return g;
}

template< typename V, typename E >
Graph<V, E>& GraphSample()
{
    static ListGraph<V, E> g(3);

    g.setEdge(0, 1, 4);
    g.setEdge(0, 2, 11);

    g.setEdge(1, 2, 2);
    g.setEdge(1, 0, 6);

    g.setEdge(2, 0, 3);

    return g;
}

int main()
{
#if 0
    // dijkstra 算法

    Graph<int, int> &g = GraphComplex<int, int>();
    //Graph<int, int> &g = GraphEasy<int, int>();
    //SharedPointer< Array<int> > p = g.dijkstra(0, 3, 65535);
    SharedPointer< Array<int> > p = g.dijkstra(0, 4, 65535);

    for(int i=0; i<p->length(); i++)
    {
        cout << (*p)[i] << " ";
    }

    cout << endl;
#else
    // floyd 算法
#if 0
    // 仅打印值
    Graph<int, int> &g = GraphSample<int, int>();
    //int r = g.floyd(0, 2, 65535);
    //cout << r << endl;

    for (int i  = 0; i < g.vCount(); i++) {
        for (int j  = 0; j < g.vCount(); j++) {
            cout << g.floyd(i, j, 65535) << " ";
        }
        cout << endl;
    }
    
#else
    // 打印路径
    Graph<int, int> &g = GraphSample<int, int>();
    SharedPointer< Array<int> > r = g.floyd(0, 2, 65535);

    for (int i  = 0; i < r->length(); i++) {
        cout << (*r)[i] << " ";
    }
    cout << endl;
#endif

#endif


    return 0;
}

#endif