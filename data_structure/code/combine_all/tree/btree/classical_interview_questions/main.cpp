#include <iostream>
#include "btree_node.h"
#include "tstring.h"

using namespace std;
using namespace DTLib;

#if 1
// 测试所需公用函数
template <typename T>
BTreeNode<T> *createTree()
{
    static BTreeNode<int> ns[9];

    for (int i = 0; i < 9; i++) {
        ns[i].value = i;
        ns[i].parent = NULL;
        ns[i].left = NULL;
        ns[i].right = NULL;
    }

    ns[0].left = &ns[1];
    ns[0].right = &ns[2];
    ns[1].parent = &ns[0];
    ns[2].parent = &ns[0];

    ns[1].left = &ns[3];
    ns[1].right = NULL;
    ns[3].parent = &ns[1];

    ns[2].left = &ns[4];
    ns[2].right = &ns[5];
    ns[4].parent = &ns[2];
    ns[5].parent = &ns[2];
    
    ns[3].left = NULL;
    ns[3].right = &ns[6];
    ns[6].parent = &ns[3];

    ns[4].left = &ns[7];
    ns[4].right = NULL;
    ns[7].parent = &ns[4];

    ns[5].left = &ns[8];
    ns[5].right = NULL;
    ns[8].parent = &ns[5];
    
    return ns;
}

template <typename T>
void printInOrder(BTreeNode<T> *node)
{
    if (node != NULL) {
        printInOrder(node->left);
        cout << node->value << " ";
        printInOrder(node->right);
    }
}

template < typename T >
void printDualList(BTreeNode<T> *node)
{
    BTreeNode<T> *g = node;

    cout << "head -> tail: " << endl;

    while( node != NULL ) {
        cout << node->value << " ";

        g = node;

        node = node->right;
    }

    cout << endl;

    cout << "tail -> head: " << endl;

    while( g != NULL ) {
        cout << g->value << " ";

        g = g->left;
    }

    cout << endl;

}

#endif

/*
 * question 1:
 * - 单度节点删除
 *      编写一个函数用于删除二叉树中的所有单度节点
 *      要求：节点删除后，其唯一的子节点代替它的位置
 * 
 *  思路：递归实现 ---> 二叉树中包含指向父节点的指针
 *  定义功能：delOdd1(node)
 *      删除node为根节点的二叉树中的单度节点
 * 
 *               | return;                          node == NULL
 *               |
 *               | (伪码描述)
 *               | parent = node->parent;           degree == 1
 * delOdd1(node) | parent->child = node->child;
 *               | node->child->parent = parent;
 *               | delOdd1(node->child);
 *               |
 *               | delOdd1(node->left);             degree == 0 or degree == 2
 *               | delOdd1(node->right);
 */
template <typename T>
BTreeNode<T> *delOdd1(BTreeNode<T> *node)
{
    BTreeNode<T> *ret = NULL;
    if (node != NULL) {
        if (((node->left != NULL) && (node->right == NULL)) ||
            ((node->left == NULL) && (node->right != NULL)) ) {
            BTreeNode<T> *parent = dynamic_cast<BTreeNode<T>*>(node->parent);
            BTreeNode<T> *node_child = (node->left != NULL) ? node->left : node->right;

            if(parent != NULL) {
                BTreeNode<T> *&parent_child = (parent->left == node) ? parent->left : parent->right;
                parent_child = node_child;
                node_child->parent = parent;
            } else {
                node_child->parent = NULL;
            }

            if (node->flag()) { // 若是堆空间创建的
                delete node;
            }

            ret = delOdd1(node_child);
        } else {
            delOdd1(node->left);
            delOdd1(node->right);
            ret = node;
        }
    }

    return ret;
}

/*
 * question 1:
 * - 单度节点删除
 *      编写一个函数用于删除二叉树中的所有单度节点
 *      要求：节点删除后，其唯一的子节点代替它的位置
 * 
 *  思路：递归实现 ---> 二叉树中不包含指向父节点的指针，仅包含左右孩子指针
 *  定义功能：delOdd2(node) // node为节点指针的引用
 *      删除node为根节点的二叉树中的单度节点
 * 
 *               | return;                          node == NULL
 *               |
 *               | (伪码描述)
 *               | node = node->child;              degree == 1
 * delOdd2(node) | delOdd2(node);
 *               | 
 *               | delOdd2(node->left);             degree == 0 or degree == 2
 *               | delOdd2(node->right);
 */
template <typename T>
void delOdd2(BTreeNode<T> *&node)
{
    if (node != NULL) {
        if (((node->left != NULL) && (node->right == NULL)) ||
            ((node->left == NULL) && (node->right != NULL)) ) {
            BTreeNode<T> *node_child = (node->left != NULL) ? node->left : node->right;

            if (node->flag()) { // 若是堆空间创建的
                delete node;
            }

            node = node_child;

            delOdd2(node);
        } else {
            delOdd2(node->left);
            delOdd2(node->right);
        }
    }
}

/*
 * question 2:
 * - 中序线索化二叉树
 *      编写一个函数用于中序线索化二叉树
 *      要求：不允许使用其他数据结构 (之前是使用了队列来进行转化)
 * 
 * 思路一：在中序遍历的同时进行线索化
 *  使用辅助指针，在中序遍历时指向当前节点的前驱节点
 *  访问当前节点时，连接与前驱节点的先后次序
 * 
 * 定义功能：InOrderThread(node, pre)
 *  node : 根节点，也是中序访问的节点
 *  pre  : 为中序遍历时的前驱节点指针
 * 
 *                          | return;                           node == NULL
 *                          |
 * inOrderThread(node, pre) | inOrderThread(node->left, pre);   node != NULL
 *                          | node->left = pre;
 *                          | pre->right = node;
 *                          | pre = node;
 *                          | inOrderThread(node->right, pre);
 */
template <typename T>
void inOrderThread(BTreeNode<T> *node, BTreeNode<T> *&pre)
{
    if (node != NULL) {
        inOrderThread(node->left, pre);
        node->left = pre;

        if (pre != NULL) {
            pre->right = node;
        }

        pre = node;

        inOrderThread(node->right, pre);
    }
}


template <typename T>
BTreeNode<T> *inOrderThread1(BTreeNode<T> *node)
{
    BTreeNode<T> *pre = NULL;

    inOrderThread(node, pre);

    while((node != NULL) && (node->left != NULL)) {
        node = node->left;
    }

    return node;
}

/*
 * question 2:
 * - 中序线索化二叉树
 *      编写一个函数用于中序线索化二叉树
 *      要求：不允许使用其他数据结构 (之前是使用了队列来进行转化)
 * 
 * 思路二：不使用中序遍历的方式，因中序遍历的节点次序正好是节点的水平次序
 *  使用辅助指针，指向转换后双向链表的头节点和尾节点
 *  根节点与左右子树转换的双线链表连接，成为完整双向链表
 * 
 * 定义功能：InOrderThread(node, head, tail)
 *  node : 根节点，也是中序访问的节点
 *  head : 转换成功后指向双向链表的首节点
 *  tail : 转换成功后指向双链表的尾节点 
 * 
 *                                | return;                             node == NULL
 *                                |
 * inOrderThread(node, head, pre) | inOrderThread(node->left, h, t);    node != NULL
 *                                | node->left = t;
 *                                | t->right = node;
 *                                | inOrderThread(node->right, h, t);
 *                                | node->right = h;
 *                                | h->left = node;
 */
template <typename T>
void inOrderThread(BTreeNode<T> *node, BTreeNode<T> *&head, BTreeNode<T> *&tail)
{
    if (node != NULL) {
        BTreeNode<T> *h = NULL;
        BTreeNode<T> *t = NULL;

        inOrderThread(node->left, h, t);

        node->left = t;

        if (t != NULL) {
            t->right = node;
        }

        head = (h != NULL) ? h : node;

        h = NULL;
        t = NULL;
        inOrderThread(node->right, h, t);
        
        node->right = h;

        if (h != NULL) {
            h->left = node;
        }

        tail = (t != NULL) ? t : node;
    }
}

template <typename T>
BTreeNode<T> *inOrderThread2(BTreeNode<T> *node)
{
    BTreeNode<T> *head = NULL;
    BTreeNode<T> *tail = NULL;

    inOrderThread(node, head, tail);

    return head;
}

int main(int argc, char **argv)
{
    BTreeNode<int> *ns = createTree<int>();

    printInOrder(ns);

    cout << endl;

#if 0
    // delOdd1 test
    ns = delOdd1(ns);

    printInOrder(ns);

    cout << endl;
    
    int a[] = {6, 7, 8};
    for (int i = 0; i < 3; i++) {
        TreeNode<int> *n = ns +a[i];
        while(n != NULL) {
            cout << n->value << " ";
            n = n->parent;
        }
        cout << endl;
    }
    cout << endl;
#endif

#if 0
    // delOdd2 test
    delOdd2(ns);

    printInOrder(ns);

    cout << endl;
#endif

#if 0
    // inOrderThread1 test
    ns = inOrderThread1(ns);

    printDualList(ns);
#endif

#if 1
    // inOrderThread2 test
    ns = inOrderThread2(ns);

    printDualList(ns);
#endif

    return 0;
}
