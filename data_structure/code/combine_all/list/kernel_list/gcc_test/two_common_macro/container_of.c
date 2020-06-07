#include <stdio.h>

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE*)0)->MEMBER)
#endif



#ifndef container_of
#define container_of(ptr, type, member) ({		         \
        const typeof(((type*)0)->member) *__mptr = (ptr);   \
        (type*)((char*)__mptr - offsetof(type, member)); })
#endif



// 若个改为下面的宏，编译器将无法做类型检查
#ifndef container_of_new
#define container_of_new(ptr, type, member) ((type*)((char*)(ptr) - offsetof(type, member)))
#endif


struct ST
{
    int i;     // 0
    int j;     // 4
    char c;    // 8
};

void method_1()
{
    int a = 0;
    int b = 0;

    int r = (
           a = 1,
           b = 2,
           a + b
                );

    printf("r = %d\n", r);
}

void method_2()
{
    int r = ( {
                  int a = 1;
                  int b = 2;

                  a + b;
              } );

    printf("r = %d\n", r);
}

void type_of()
{
    int i = 100;
    typeof(i) j = i; // int j = i;
    const typeof(j) *p = &j; // const int *p = &j;

    printf("sizeof(j) = %ld\n", sizeof(j));
    printf("j = %d\n", j);
    printf("*p = %d\n", *p);
}

int main()
{

     method_1();
     method_2();

     type_of();

#if 1
    struct ST s = {0};
    char* pc = &s.c;

	int e = 0;
	int *pe = &e;

    
	struct ST* pst = container_of(pc, struct ST, c); // 将会多报一个警告
	//struct ST* pst = container_of(pe, struct ST, c); // 将会多报一个警告
    //struct ST* pst = container_of_new(pe, struct ST, c);

    printf("&s =  %p\n", &s);
    printf("pst = %p\n", pst);
#endif
    return 0;
}
