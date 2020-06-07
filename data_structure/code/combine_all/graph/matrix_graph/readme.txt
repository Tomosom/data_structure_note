邻接矩阵法中的残留问题
1.
MatrixGraph无法动态 添加/删除 顶点!!!

2.
template <int N, typename V, typename E>
class MatrixGraph : public Graph<V, E> {
protected:

    V *m_vertexes[N];
    E *m_edges[N][N]; /* N = 1000时，邻接矩阵的体积为 4(或8)*1000*1000字节；
                         因此，图对象创建时的体积约为4MB(或8MB) */

    int m_eCount;

public:
	// ...

};
