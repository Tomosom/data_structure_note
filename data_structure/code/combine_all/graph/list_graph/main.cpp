#include <iostream>
#include "list_graph.h"

using namespace std;
using namespace DTLib;

#include "../DFS_recurse.cpp"

int main(int argc, char **argv)
{
#if 0
    // 邻接链表法基本功能测试

    // ListGraph<char, int> g(4);
    // g.setVertex(0, 'A');
    // g.setVertex(1, 'B');
    // g.setVertex(2, 'C');
    // g.setVertex(3, 'D');
    
    ListGraph<char, int> g;
    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    
    // g.removeVertex();

    for (int i = 0; i < g.vCount(); i++) {
        cout << i << " : " << g.getVertex(i) << endl;
    }

    g.setEdge(0, 1, 5);
    g.setEdge(0, 3, 6);
    g.setEdge(1, 2, 8);
    g.setEdge(2, 3, 2);
    g.setEdge(3, 1, 9);

    cout << "W(0, 1) : " << g.getEdge(0, 1) << endl;
    cout << "W(0, 3) : " << g.getEdge(0, 3) << endl;
    cout << "W(1, 2) : " << g.getEdge(1, 2) << endl;
    cout << "W(2, 3) : " << g.getEdge(2, 3) << endl;
    cout << "W(3, 1) : " << g.getEdge(3, 1) << endl;

    cout << "eCount : " << g.eCount() << endl;

    // g.removeEdge(3, 1);
    cout << "eCount : " << g.eCount() << endl;
    // cout << "W(3, 1) : " << g.getEdge(3, 1) << endl; // 抛异常

    SharedPointer< Array<int> > aj = g.getAdjacent(0);
    for (int i = 0; i < aj->length(); i++) {
        cout << (*aj)[i] << endl;
    }

    cout << "ID(1) : " << g.ID(1) << endl;
    cout << "OD(1) : " << g.OD(1) << endl;
    cout << "TD(1) : " << g.TD(1) << endl;

    g.removeVertex();

    cout << "eCount : " << g.eCount() << endl;
    cout << "W(0, 1) : " << g.getEdge(0, 1) << endl;
    cout << "W(1, 2) : " << g.getEdge(1, 2) << endl;
    // cout << "W(2, 3) : " << g.getEdge(2, 3) << endl;
#endif

#if 1
    // 遍历测试
    ListGraph<char, int> g;
    const char *VD = "ABEDCGFHI";

    for (int i = 0; i < 9; i++) {
        g.addVertex(VD[i]);
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

