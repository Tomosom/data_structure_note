#include <stdio.h>

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE*)0)->MEMBER)
#endif

struct ST {
	int i;
	int j;
	char c;
};

void func(struct ST *pst)
{
	int *pi = &(pst->i);	
	int *pj = &(pst->j);
	char *pc = &(pst->c);	


	printf("pst = %p\n", pst);

	printf("pi  = %p\n", pi);
	printf("pj  = %p\n", pj);
	printf("pc  = %p\n", pc);
}


int main(int argc, char **argv)
{
	struct ST st = {0};

	func(&st);

	func(NULL);
	
	printf("offsetof i : %ld\n", offsetof(struct ST, i));
	printf("offsetof j : %ld\n", offsetof(struct ST, j));
	printf("offsetof c : %ld\n", offsetof(struct ST, c));

	
	return 0;
}

