#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <cstdlib>
//#include <cstring>
/* 顶层父类创建原因：适配不同编译器的申请对空间操作 */
namespace DTLib{

class Object {

public:
	/* 重载new与delete函数，与Windows的区别，形参类型不同
		Windows：size_t ：unsigned int
		Linux 64bit: long unsigned int
	*/
	void *operator new(size_t size) throw();
	void operator delete(void *p);
	void *operator new[](size_t size) throw();
	void operator delete[](void *p);
	// 解决list.h中的find操作，对象为类时，==判断错误的问题
	bool operator==(const Object &obj);
 	bool operator!=(const Object &obj);
	virtual ~Object() = 0;

};

}

#endif