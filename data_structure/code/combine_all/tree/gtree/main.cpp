#include <iostream>
#include "gtree.h"

using namespace std;
using namespace DTLib;

int main()
{
    GTree<char> t;
    GTreeNode<char> *node = NULL;

#if 1

#if 1 // 此开关测试clear() bug问题
    GTreeNode<char> root; // 栈上定义的节点
    root.value = 'A';
    root.parent = NULL;
    t.insert(&root);
#else

    GTreeNode<char> *root = new GTreeNode<char>; // 堆上定义的节点
    root->value = 'A';
    root->parent = NULL;
    t.insert(root);

#endif

#else

    try {
        t.insert('A', NULL);
    }
    catch (const Exception &e) {
        cout << e.message() << endl;
    }

#endif


    node = t.find('A');
    t.insert('B', node);
    t.insert('C', node);
    t.insert('D', node);

    node = t.find('B');
    t.insert('E', node);
    t.insert('F', node);
    
    node = t.find('E');
    t.insert('K', node);
    t.insert('L', node);
    
    node = t.find('C');
    t.insert('G', node);
    
    // node = t.find('G');
    // t.insert('N', node);
    
    node = t.find('D');
    t.insert('H', node);
    t.insert('I', node);
    t.insert('J', node);
  
    node = t.find('H');
    t.insert('M', node);

    cout << t.count() << endl; // 获取节点个数测试
    cout << t.height() << endl; // 获取节点高度测试
    cout << t.degree() << endl; // 获取节点的度测试

    for (t.begin(); !t.end(); t.next())
    {
        cout << t.current() << endl;
    }

#if 0 // remove test
    //t.clear(); // clear test
    //t.remove('D'); // remove test
    //t.remove(t.find('D')); // remove test
    SharedPointer< Tree<char> > p = t.remove(t.find('D')); // remove test


    // 通过叶节点遍历到根节点
    const char *s = "KLFGMIJ";
    for(int i = 0; i < 7; i++) {
        //TreeNode<char> *node = t.find(s[i]);
        TreeNode<char> *node = p->find(s[i]); // 打印被删除的子树
        while(node != NULL) {
            cout << node->value << " ";
            node = node->parent;
        }

        cout << endl;
    }
#endif
    return 0;
}