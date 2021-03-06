#include <iostream>

using namespace std;

struct Node {
    int value;
    Node *next;
};

Node *create_list(int v, int len)
{
    Node *ret = NULL;
    Node *slider = NULL;

    for (int i = 0; i < len; i++) {
        Node *n = new Node();

        n->value = v++;
        n->next = NULL;

        if (slider == NULL) {
            slider = n;
            ret = n;
        } else {
            slider->next = n;
            slider = n;
        }
    }

    return ret;
}

void destroy_list(Node *list)
{
    while(list) {
        Node *del = list;
        list = list->next;
        delete del;
    }
}

void print_list(Node *list)
{
    while(list) {
        cout << list->value << "->";
        list = list->next;
    }
    cout << "NULL" << endl;
}

// 单链表递归转置
Node *reverse(Node *list)
{
    if ((list == NULL) || (list->next == NULL)) {
        return list;
    } else {
        Node *guard = list ->next;
        Node *ret = reverse(list->next);
        guard->next = list;
        list->next = NULL;
        return ret;
    }

}

// 单向已排好序的链表的合并，合并后仍是单向有序的
Node *merge(Node *list1, Node *list2)
{
    if (list1 == NULL) {
        return list2;
    } else if (list2 == NULL) {
        return list1;
    } else if (list1->value < list2->value) {
#if 0
        Node *list1_ = list1->next;
        Node *list = merge(list1_, list2);
        list1->next = list;
        return list1;
#else
        return (list1->next = merge(list1->next, list2), list1); // 逗号表达式
#endif
    } else {
#if 0
        Node *list2_ = list2->next;
        Node *list = merge(list2_, list1);
        list2->next = list;
        return list2;
#else
        return (list2->next = merge(list2->next, list1), list2);
#endif
    }
}

// 逆序打印单链表中的偶数节点
void r_print_even(Node *list)
{
    if (list != NULL) {
        r_print_even(list->next);
        if ((list->value % 2) == 0) {
            cout << list->value << endl;
        }
    }
}

/*********************** test *************************/
// 单链表转置测试
void test1()
{
    Node *list = create_list(3, 10);

    print_list(list);

    list = reverse(list);

    print_list(list);

    destroy_list(list);
}

// merge测试
void test2()
{
    Node *list1 = create_list(1, 5);
    Node *list2 = create_list(2, 6);

    print_list(list1);
    print_list(list2);

    Node *list = merge(list1, list2);

    print_list(list);

    destroy_list(list);
}

// 逆序打印单链表中的偶数节点测试
void test3()
{
    Node *list = create_list(2, 5);
    print_list(list);

    r_print_even(list);
    destroy_list(list);
}

int main(int argc, char **argv)
{
    //test1();
    //test2();
    test3();

    return 0;
}