#include <iostream>
#include "smart_pointer.h"
#include "shared_pointer.h"
using namespace std;
using namespace DTLib;

struct Test {
    int value;
    Test() : value(0)
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

    const SharedPointer<Test> sp = new Test();
    //sp->value = 5; // error


    SharedPointer<Test> sp0 = new Test();
    SharedPointer<Test> sp1 = sp0;
    SharedPointer<Test> sp2 = NULL;

    sp2 = sp1;

    sp2->value = 100;

    cout << sp0->value << endl;
    cout << sp1->value << endl;
    cout << sp2->value << endl;

    //sp2.clear();

    cout << (sp2 == sp0) << endl;
    cout << (sp2 != sp0) << endl;

	return 0;

}