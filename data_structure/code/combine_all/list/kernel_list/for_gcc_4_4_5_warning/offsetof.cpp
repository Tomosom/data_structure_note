#include <iostream>

//#undef offsetof

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE*)0)->MEMBER)

/* 解决 invalid access to non-static data member ‘ST::i’  of NULL object */
//#define offsetof(TYPE, MEMBER) (((size_t)&((TYPE*)1)->MEMBER) - 1)

//#define offsetof(type, member) ((size_t)((char*)(&((type*)1)->member) - 1))

/* 相当于使用编译器自带的 offsetof 宏 */
//#define offsetof(type, member) __builtin_offsetof(type, member)

//#define offsetof(s,m)   (size_t)(&reinterpret_cast<const volatile char&>((((s*)0x11)->m)) - 0x11)

#endif




using namespace std;

class object {
public:
	int oo;
};

struct ST : public object{
//struct ST{
	int i;
	int j;
	char c;
};


int main(int argc, char **argv)
{
	struct ST st;

	cout << "offsetof i : " << offsetof(struct ST, i) << endl;
	cout << "offsetof j : " << offsetof(struct ST, j) << endl;
	cout << "offsetof c : " << offsetof(struct ST, c) << endl;

	return 0;
}

