/*
 * DFS : Depth First Search 深度优先遍历
 *  以二叉树先序遍历的思想对图进行遍历
 * 
 * 递归版深度优先算法
 *  - 定义功能: DFS(graph, vex)
 *      以顶点vex为起始顶点深度优先遍历graph
 * 
 *                 | visit(vex);            adjacent(vex) == NULL (无邻接顶点)
 *                 | return;
 * DFS(graph, vex) |
 *                 | visit(vex);            adjacent(vex) != NULL (有邻接顶点)
 *                 | aj = getAdjacent(vex);
 *                 | DFS( graph, { aj } );
 */
template <typename V, typename E>
void DFS(Graph<V, E> &g, int v, Array<bool> &visited)
{
    if ((0 <= v) && (v <= g.vCount())) {
        cout << v << endl;
        visited[v] = true;

        SharedPointer< Array<int> > aj = g.getAdjacent(v);

        for (int i = 0; i < aj->length(); i++) {
            if ( !visited[(*aj)[i]] ) {
                DFS(g, (*aj)[i], visited);
            }
        }

    } else {
        THROW_EXCEPTION(InvalidParameterException, "Index v is invalid ...");
    }
}

template <typename V, typename E>
void DFS(Graph<V, E> &g, int v)
{
    DynamicArray<bool> visited(g.vCount());

    for (int i = 0; i < visited.length(); i++) {
        visited[i] = false;
    }

    DFS(g, v, visited);
}