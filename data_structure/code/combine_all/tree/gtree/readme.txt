gtree : general tree

gtree_node.h_v1.0 & gtree.h_v1.0
    完成find, insert, clear操作后的版本

gtree_node.h_v1.1 & gtree.h_v1.0
    解决上一版本中，当节点是在栈空间申请时，clear操作导致free栈区的错误
    解决方案：工厂模式
        1. 在GTreeNode中增加保护成员变量m_flag
        2. 将GTreeNode中的operator new 重载为保护成员函数(外面不能直接new)
        3. 提供工厂方法 GTreeNode<T> *NewNode()   --静态成员函数
        4. 在工厂方法中new新节点并将m_flag设置为true

main.cpp
