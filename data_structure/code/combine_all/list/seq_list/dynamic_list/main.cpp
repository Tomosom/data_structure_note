#include <iostream>
#include "link_list.h"
#include "dynamic_list.h"
using namespace std;
using namespace DTLib;

// 若不改善，泛指类型用此类会有问题
// 如果是自定义类类型，最好也继承顶层父类
class Test : public Object{

    int i;
public:
    Test(int v = 0)
    {
        i = v;
    }

    // 要定义find方法查找依据，最好重写==重载函数，默认是比较地址
    bool operator==(const Test &obj)
    {
        return (this->i == obj.i);
    }

};

int main(int argc, char **argv)
{
    DynamicList<Test> dsf(5);

    Test t1(1);
    Test t2(2);
    Test t3(3);
    LinkList<Test> list0;
    list0.insert(0, t1);
    list0.insert(0, t2);
    list0.insert(0, t3);
    cout << "test find : " << list0.find(3) << endl;


    LinkList<int> list;
    for(int i = 0; i < 5; i++) {
        list.insert(0, i);
    }
    cout << "int find : " << list.find(2) << endl;

    return 0;

}
