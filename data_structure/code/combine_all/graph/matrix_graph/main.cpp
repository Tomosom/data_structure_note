#include <iostream>
#include "matrix_graph.h"

using namespace std;
using namespace DTLib;

#include "../DFS_recurse.cpp"

int main(int argc, char **argv)
{
#if 0
    // 邻接矩阵法基本功能测试
    MatrixGraph<3, int, int> g;

    g.setEdge(0, 1, 1);
    g.setEdge(1, 0, 2);
    g.setEdge(1, 2, 3);

    cout << "vCount : " <<g.vCount() << endl;
    cout << "eCount : " <<g.eCount() << endl;
    cout << "ID(1) : " << g.ID(1) << endl;
    cout << "OD(1) : " << g.OD(1) << endl; 
    cout << "TD(1) : " << g.TD(1) << endl;
    
    cout << "W(0, 1) : " << g.getEdge(0, 1) << endl;
    cout << "W(1, 0) : " << g.getEdge(1, 0) << endl;
    cout << "W(1, 2) : " << g.getEdge(1, 2) << endl;

    SharedPointer< Array<int> > aj = g.getAdjacent(1);
    for (int i = 0; i < aj->length(); i++) {
        cout << (*aj)[i] << " ";
    }
    cout << endl;

    cout << "delete edge : " << endl;
    g.removeEdge(0, 1);
    cout << "eCount : " <<g.eCount() << endl;

    g.setVertex(0, 100);
    cout << "V(0) : " << g.getVertex(0) << endl;
    // cout << "W(0, 1) : " << g.getEdge(0, 1) << endl; // 抛异常
#endif

#if 1
    // 遍历测试
    MatrixGraph<9, char, int> g;
    const char *VD = "ABEDCGFHI";

    for (int i = 0; i < 9; i++) {
        g.setVertex(0, VD[i]);
    }

    g.setEdge(0, 1, 0);
    g.setEdge(1, 0, 0);

    g.setEdge(0, 3, 0);
    g.setEdge(3, 0, 0);

    g.setEdge(0, 4, 0);
    g.setEdge(4, 0, 0);

    g.setEdge(1, 2, 0);
    g.setEdge(2, 1, 0);

    g.setEdge(1, 4, 0);
    g.setEdge(4, 1, 0);

    g.setEdge(2, 5, 0);
    g.setEdge(5, 2, 0);

    g.setEdge(3, 6, 0);
    g.setEdge(6, 3, 0);

    g.setEdge(4, 6, 0);
    g.setEdge(6, 4, 0);

    g.setEdge(6, 7, 0);
    g.setEdge(7, 6, 0);

    g.setEdge(7, 8, 0);
    g.setEdge(8, 7, 0);

    // SharedPointer< Array<int> > sa = g.BFS(0);  // BFS遍历
    SharedPointer< Array<int> > sa = g.DFS(0);  // DFS遍历
    
    for (int i = 0; i < sa->length(); i++) {
        cout << (*sa)[i] << " ";
    }
    cout << endl;


#endif

    DFS(g, 0);

    return 0;
}