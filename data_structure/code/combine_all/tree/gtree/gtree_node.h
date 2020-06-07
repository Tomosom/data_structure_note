#ifndef GTREE_NODE_H
#define GTREE_NODE_H

#include "tree_node.h"
#include "link_list.h"

namespace DTLib {

template <typename T>
class GTreeNode : public TreeNode<T> {


public:
    LinkList<GTreeNode<T> *> child;

    static GTreeNode<T> *NewNode()
    {
        GTreeNode<T> *ret = new GTreeNode<T>();
        if (ret != NULL) {
            ret->m_flag = true;
        }
        return ret;
    }


};


}

#endif
