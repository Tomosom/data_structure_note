#include "object.h"
#include <iostream>

using namespace std;

namespace DTLib{

void *Object::operator new(size_t size) throw() /* 表明当前的重载函数不会跑出任何异常 */
{
	//cout << "Object::operator new : " << size << endl;
	return malloc(size);
}

void Object::operator delete(void *p)
{
	//cout << "Object::operator delete : " << p << endl;
	free(p);
}

void *Object::operator new[](size_t size) throw()
{
	return malloc(size);

}
void Object::operator delete[](void *p)
{
	free(p);

}

bool Object::operator==(const Object &obj)
{
    return (this == &obj);
}

bool Object::operator!=(const Object &obj)
{
    return (this != &obj);
}

Object::~Object()
{

}


}