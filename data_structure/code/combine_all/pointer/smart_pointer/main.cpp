#include <iostream>
#include "smart_pointer.h"

using namespace std;
using namespace DTLib;

struct Test {
    Test()
    {
        cout << "Test()" << endl;
    }
    ~Test()
    {
        cout << "~Test()" << endl;
    }

};

int main(int argc, char **argv)
{
    SmartPointer<Test> t = new Test;

    SmartPointer<Test> p;
    p = t; // 只有一个指针能指向该对象


	return 0;

}