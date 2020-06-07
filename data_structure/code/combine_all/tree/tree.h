/*
 *           Object
 *        ^         ^
 *        |         |
 *      Tree ----> TreeNode
 */

#ifndef TREE_H
#define TREE_H

#include "tree_node.h"
#include "shared_pointer.h"

namespace DTLib {

template <typename T>
class Tree : public Object {
protected:
    TreeNode<T> *m_root;
    
    // 定义成proteced,禁止两棵树之间相互复制
    Tree(const Tree<T>&);
    Tree<T> &operator = (const Tree<T> &);
public:
    Tree() { m_root = NULL; }
    virtual bool insert(TreeNode<T> *node) = 0;
    virtual bool insert(const T &value, TreeNode<T> *parent) = 0;
    virtual SharedPointer< Tree<T> > remove(const T &value) = 0;
    virtual SharedPointer< Tree<T> > remove(TreeNode<T> *node) = 0;
    virtual TreeNode<T> *find(const T &value) const = 0;
    virtual TreeNode<T> *find(TreeNode<T> *node) const = 0;
    virtual TreeNode<T> *root() const = 0; // 访问树的根节点

    // 获取树的属性
    virtual int degree() const = 0; // 获取树的度
    virtual int count() const = 0;  // 获取树的节点数
    virtual int height() const = 0; // 获取树的高度
    virtual void clear() = 0;       // 清空树中的元素
    
    /*
     * 层次遍历算法
     * 原料：class LinkQueue<T>;
     * 游标：LinkQueue<T>::front();
     * 思想：
     *  begin() -> 将根节点压入队列中
     *  current() -> 访队头元素指向的数据元素
     *  next() -> 队头元素弹出，将队头元素的孩子压入队列中(核心)
     *  end() -> 判断队列是否为空
     * 使用：
     *  for(tree.begin(); !tree.end(); tree.next()) {
     *      tree.current();
     *  }
     */
    virtual bool begin() = 0;
    virtual bool end() = 0;
    virtual bool next() = 0;
    virtual T current() = 0;
};


}

#endif