#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "object.h"

namespace DTLib {

// 用来描述树里面的节点
template <typename T>
class TreeNode : public Object {
protected:
    // 工厂方法相关函数移动到父类节点
    bool m_flag;

    TreeNode(const TreeNode<T>&);
    TreeNode &operator = (const TreeNode<T>&); // 不能被复制

    void *operator new (size_t size) throw() // 声明一个不抛出异常的函数
    {
        return Object::operator new(size);
    }

public:
    T value;
    TreeNode<T> *parent; // 指向父节点的指针

    TreeNode()
    {
        m_flag = false;
        parent = NULL;
    }

    bool flag()
    {
        return m_flag;
    }
    
    virtual ~TreeNode() = 0;
};

// 可以在头文件中定义抽象类的析构函数
template <typename T>
TreeNode<T>::~TreeNode()
{
    
}

}

#endif