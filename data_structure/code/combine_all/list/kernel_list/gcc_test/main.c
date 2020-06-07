#include <stdio.h>
#include <stdlib.h>
#include "linux_list.h"

void list_demo_1()  // list_head放在结构体前面的情形
{
    int i = 0;

    struct Node {
        struct list_head head;
        int value;
    };

    struct Node l = {0};
    struct list_head *list = (struct list_head *)&l;    
    struct list_head *slider;

    INIT_LIST_HEAD(list);

    printf("insert begin ...\n");
    for(i = 0; i < 5; i++) {
        struct Node *n = (struct Node *)malloc(sizeof(struct Node));
        n->value = i;
        list_add_tail((struct list_head*)n, list); // 尾插法
    }

    list_for_each(slider, list) {
        printf("%d\n", ((struct Node*)slider)->value);
    }
    printf("insert end ...\n");

    printf("delete begin ...\n");
    list_for_each(slider, list) {
        if(((struct Node*)slider)->value == 3) {
            list_del(slider);
            free(slider);
            break;
        }
    }
    list_for_each(slider, list) {
        printf("%d\n", ((struct Node*)slider)->value);
    }
    printf("delete end ...\n");
}


void list_demo_2() // list_head放在结构体后面的情形
{
    int i = 0;    

    struct Node {
        int value;
        struct list_head head;
    };

    struct Node l = {0};
    struct list_head *list = &l.head;    
    struct list_head *slider;

    INIT_LIST_HEAD(list);

    printf("insert begin ...\n");
    for(i = 0; i < 5; i++) {
        struct Node *n = (struct Node *)malloc(sizeof(struct Node));
        n->value = i;
        list_add(&n->head, list); // 头插法
    }

    list_for_each(slider, list) {
        printf("%d\n", list_entry(slider, struct Node, head)->value);
    }
    printf("insert end ...\n");

    printf("delete begin ...\n");
    list_for_each(slider, list) {
        struct Node *n = list_entry(slider, struct Node, head);
        if(n->value == 3) {
            list_del(slider);
            free(n);
            break;
        }
    }
    list_for_each(slider, list) {
        printf("%d\n", list_entry(slider, struct Node, head)->value);
    }
    printf("delete end ...\n");
}

int main(int argc, char **argv)
{
    list_demo_2();

    return 0;
}
