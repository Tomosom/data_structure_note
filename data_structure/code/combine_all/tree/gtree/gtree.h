/*
 *           Object
 *        ^         ^
 *        |         |
 *      Tree ----> TreeNode
 *        ^           ^
 *        |           |
 *     GTree -----> GTreeNode 
 */

#ifndef GTREE_H
#define GTREE_H

#include "tree.h"
#include "gtree_node.h"
#include "exception.h"
#include "link_queue.h"

#if 0 // for test
#include <iostream>
using namespace std;
#endif
//#define MAX(a, b) ((a) > (b) ? (a) : (b))
namespace DTLib {

template <typename T>
class GTree : public Tree<T> {
    // implementation
protected:
    LinkQueue<GTreeNode<T>*> m_queue; // 用作层次遍历

    // 第二个参数是一个引用， 这个引用是一个指针的别名
    // 将node为根节点的字树从原来的树中删除
    // ret作为子树返回（ret指向对空间中的树对象）
    void remove(GTreeNode<T> *node, GTree<T> *&ret)
    {
        ret = new GTree<T>();
        if (ret == NULL) {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
        } else {
            if (root() == node) {
                this->m_root = NULL;
            } else {
                LinkList<GTreeNode<T>*> &child = dynamic_cast<GTreeNode<T>*>(node->parent)->child;
                child.remove(child.find(node));
                node->parent = NULL;
            }

            ret->m_root = node;
        }
    }

    GTreeNode<T> *find(GTreeNode<T> *node, const T &value) const
    {
        GTreeNode<T> *ret  = NULL;

        if (node != NULL) {
            if (node->value == value) {
                return node;
            } else {
                for (node->child.move(0); !node->child.end() && (ret == NULL); node->child.next()) {
                    ret = find(node->child.current(), value);
                }
            }
        }

        return ret;
    }

    GTreeNode<T> *find(GTreeNode<T> *node, const GTreeNode<T> *obj) const
    {
        GTreeNode<T> *ret  = NULL;

        if (node == obj) {
            return node;
        } else {
            if (node != NULL) {
                for (node->child.move(0); !node->child.end() && (ret ==NULL); node->child.next()) {
                    ret = find(node->child.current(), obj);
                }
            }
        }

        return ret;
    }

    // for clear()
    void free(GTreeNode<T> *node) 
    {
        if (node != NULL) {
            for (node->child.move(0); !node->child.end(); node->child.next()) {
                free(node->child.current());
            }

            if (node->flag()) {
                delete node;
            }
#if 0 // for test
            else {
                cout << node->value << endl;
            }
#endif
        }
    }

    int count(GTreeNode<T> *node) const
    {
        int ret = 0;

        if(node != NULL) {
            ret = 1; // 根节点
            for(node->child.move(0); !node->child.end(); node->child.next()) {
                ret += count(node->child.current());
            }
        }
        return ret;
    }

    int height(GTreeNode<T> *node) const
    {
        int ret = 0;

        if(node != NULL) {
            for(node->child.move(0); !node->child.end(); node->child.next()) {
                int h = height(node->child.current());
                ret = ret > h ? ret : h;
            }
            ret += 1;
        }
        return ret;
    }

    int degree(GTreeNode<T> *node) const
    {
        int ret = 0;

        if (node != NULL) {
            ret = node->child.length();

            for (node->child.move(0); !node->child.end(); node->child.next()) {
                int d = degree(node->child.current());
                ret = ret > d ? ret : d;
            }
        }

        return ret;
    }
public:
    GTree() 
    {

    }

    bool insert(TreeNode<T> *node) // 插入新节点
    {
        bool ret = true;
        
        if (node != NULL) {
            if (this->m_root == NULL) {
                node->parent = NULL;
                this->m_root = node;
            } else {
                GTreeNode<T> *np = find(node->parent);
                if (np != NULL) {
                    // 判断要插入的新节点是否已经存在于树中
                    GTreeNode<T> *n = dynamic_cast<GTreeNode<T>*>(node);
                    if (np->child.find(n) < 0) {
                        np->child.insert(n);
                    }
                } else {
                    THROW_EXCEPTION(InvalidParameterException, "Already existed tree node ...");
                }
            }
        } else {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node cannot be NULL ...");
        }

        return ret;
    }
    bool insert(const T &value, TreeNode<T> *parent) // 插入数据元素
    {
        bool ret = true;
        GTreeNode<T> *node = GTreeNode<T>::NewNode();
        if (node != NULL) {
            node->value = value;
            node->parent = parent;
            insert(node);
        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree node ...");
        }

        return ret;
    }

    // 返回指向Tree的智能指针
    // 用智能指针管理返回的树的生命周期
    SharedPointer< Tree<T> > remove(const T &value)
    {
        GTree<T> *ret = NULL;
        GTreeNode<T> *node = find(value);

        if (node == NULL) {
            THROW_EXCEPTION(InvalidParameterException, "Can not find the node via parameter value ...");
        } else {
            remove(node, ret);
            m_queue.clear(); // 遍历所需队列
        }

        return ret;
    }
    SharedPointer< Tree<T> > remove(TreeNode<T> *node)
    {
        GTree<T> *ret = NULL;
        node = find(node);

        if (node == NULL) {
            THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalid ...");
        } else {
            remove(dynamic_cast<GTreeNode<T>*>(node), ret); // 需强转，不然报错
            m_queue.clear(); // 遍历所需队列
        }

        return ret;
    }

    /*
     * 定义功能：find(node, value)
     * - 在node为根节点的树中查找value所在的节点
     * 
     *                   | return node;                 node->value == value
     * find(node, value) |
     *                   | find(node->child, value);    node->value != value
     */
    GTreeNode<T> *find(const T &value) const // 以值的方式查找
    {
        return find(root(), value);
    }
    /*
     * 定义功能：find(node, obj)
     * - 在node为根节点的树中查找是否存在obj节点
     * 
     *                 | return node;               node == obj
     * find(node, obj) |
     *                 | find(node->child, obj);    node != obj
     */
    GTreeNode<T> *find(TreeNode<T> *node) const // 以节点的方式查找
    {
        return find(root(), dynamic_cast<GTreeNode<T> *>(node));
    }
    
    GTreeNode<T> *root() const // 访问树的根节点
    {
        return dynamic_cast<GTreeNode<T>*>(this->m_root);
    }
    /* 获取树的属性 */
    /*
     *               | return 0;                                        node == NULL
     *  degree(node) |
     *               | MAX{ degree(node->child),
     *                      node->child.length) }; node != NULL
     */
    int degree() const // 递归方法，获取树的度, 结点拥有的子树数目成为结点的度，树的度定义为所有结点中度的最大值
    {
        return degree(root());
    }

    /*
     *             | return 0;                 node == NULL
     *             |
     * count(node) | return 1;                 node->child.length == 0
     *             |
     *             | count(node->child) + 1;   node->child.length > 0
     */
    int count() const  // 递归方法，获取树的节点数
    {
        return count(root());
    }

    /*
     *              | return 0;                            node == NULL
     *              |
     * height(node) | return 1;                            node->child.length == 0
     *              |
     *              | return MAX{height(node->child)} + 1; node->child.length > 0
     */
    int height() const // 递归方法，获取树的高度
    {
        return height(root());
    }

    // 清空树中的元素
    /*
     * free(node)
     * - 清除node为根节点的树
     * - 释放树中的每一个节点
     * 
     *            | return;             node == NULL
     * free(node) |
     *            | free(node->child);  node != NULL
     *            | delete node;
     */
    void clear()
    {
        free(root());
        this->m_root = NULL;
        m_queue.clear(); //遍历所需的队列
    }
#if 1
    // 树形结构的层次遍历 相关函数
    bool begin() // 初始化，准备进行遍历访问
    {
        bool ret = (root() != NULL);
        if (ret) {
            m_queue.clear();
            m_queue.add(root());
        }
        return ret;
    }
    bool end() // 判断游标是否达到尾部
    {
        return (m_queue.length() == 0);
    }
    bool next() // 移动游标，指向下一个节点
    {
        bool ret = (m_queue.length() > 0);
        if (ret) {
            GTreeNode<T> *node = m_queue.front();
            m_queue.remove();
            for(node->child.move(0); !node->child.end(); node->child.next()) {
                m_queue.add(node->child.current());
            }
        }

        return ret;
    }
    T current() // 获取游标所指定的数据元素
    {
        if (!end()) {
            return m_queue.front()->value;
        } else {
            THROW_EXCEPTION(InvalidOperationException, "No value at current position ...");
        }
    }
#endif

    ~GTree()
    {
        clear();
    }

};

}


#endif
