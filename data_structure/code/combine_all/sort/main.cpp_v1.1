#include <iostream>
#include <ctime>
#include "sort.h"


using namespace std;
using namespace DTLib;

struct Test : public Object {
    int id;
    int data1[1000];
    double data2[500];

    bool operator < (const Test &obj)
    {
        return id < obj.id;
    }

    bool operator > (const Test &obj)
    {
        return id > obj.id;
    }

    bool operator <= (const Test &obj)
    {
        return id <= obj.id;
    }

    bool operator >= (const Test &obj)
    {
        return id >= obj.id;
    }
};

// 定义代理类
class TestProxy : public Object {
protected:
    Test *m_pTest;
public:
    // TestProxy(Test *pTest)
    // {
    //     m_pTest = pTest;
    // }

    int id()
    {
        return m_pTest->id;
    }

    int *data1()
    {
        return m_pTest->data1;
    }

    double *data2()
    {
        return m_pTest->data2;
    }

    Test &test() const
    {
        return *m_pTest;
    }

    // 代理类的比较
    bool operator < (const TestProxy &obj)
    {
        return test() < obj.test();
    }

    bool operator > (const TestProxy &obj)
    {
        return test() > obj.test();
    }

    bool operator <= (const TestProxy &obj)
    {
        return test() <= obj.test();
    }

    bool operator >= (const TestProxy &obj)
    {
        return test() >= obj.test();
    }

    // 重载赋值
    Test &operator = (Test &test)
    {
        m_pTest = &test;
        return test; 
    }
};

Test t[1000];
TestProxy pt[1000];

int main(int argc, char **argv)
{
    clock_t begin = 0;
    clock_t end = 0;

#if 0 // 不适用代理类的情形
    for (int i = 0; i < 1000; i++) {
        t[i].id = i;
    }

    begin = clock();
    Sort::Bubble(t, 1000, false); // 以冒泡排排序为例，因冒泡排序交换次数较多
    end = clock();

    cout << "time : " << (end - begin) << endl;

#if 0
    for (int i = 0; i < 1000; i++) {
        cout << t[i].id << endl;
    }
#endif

#else // 使用代理类的情形

    for (int i = 0; i < 1000; i++) {
        t[i].id = i;
        pt[i] = t[i]; // 使用代理，两个数组里的元素一一映射
    }

    begin = clock();
    Sort::Bubble(pt, 1000, false); // 以冒泡排排序为例，因冒泡排序交换次数较多
    end = clock();

    cout << "time : " << (end - begin) << endl;

#if 1
    for (int i = 0; i < 1000; i++) {
        cout << t[i].id << " : " << pt[i].id() << endl;
    }
#endif

#endif

    return 0;
}
