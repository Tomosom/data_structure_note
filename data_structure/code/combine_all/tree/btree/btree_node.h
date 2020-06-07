#ifndef BTREE_NODE_H
#define BTREE_NODE_H

#include "tree_node.h"

namespace DTLib {

enum BTNodePos {
    ANY,
    LEFT,
    RIGHT
};

template <typename T>
class BTreeNode : public TreeNode<T> {
public:
    BTreeNode<T> *left;
    BTreeNode<T> *right;

    BTreeNode()
    {
        left = NULL;
        right = NULL;
    }

    // factory pattern
    static BTreeNode<T> *NewNode()
    {
        BTreeNode<T> *ret = new BTreeNode<T>();
        if (ret != NULL) {
            ret->m_flag = true;
        }
        return ret;
    }
    // ...

};




}


#endif