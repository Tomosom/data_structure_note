#include <iostream>
#include "static_stack.h"

using namespace std;
using namespace DTLib;

class Test : public Object {
public:
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
    // 存在的缺陷：当存储类型为类类型时，StaticStack的对象在创建时，会多次调用元素类型的构造函数，影响效率
    // 解决：使用链式栈，link_stack.h
    StaticStack<Test, 10> stack;

    cout << stack.size() << endl;

#if 0
    StaticStack<int, 5> stack;
    try {
        stack.pop();
    }
    catch(const Exception &e) {
        cout << e.message() << endl;
        cout << e.location() << endl;
    }

    for(int i = 0; i < 5; i++) {
        stack.push(i);
    }

    while(stack.size() > 0) {
        cout << stack.top() << endl;
        stack.pop();
    }
#endif
    return 0;
}
