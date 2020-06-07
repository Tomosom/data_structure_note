#include <iostream>
#include "object.h"

using namespace std;
using namespace DTLib;

struct Test : public Object {
    int key1; // high
    int key2; // low

    Test(int k1, int k2)
    {
        key1 = k1;
        key2 = k2;
    }

    bool operator == (const Test &t)
    {
        return (key1 == t.key1) && (key2 == t.key2);
    }

    bool operator != (const Test &t)
    {
        return !(*this == t);
    }

    bool operator < (const Test &t)
    {
        return (key1 < t.key1) || ((key1 == t.key1) && (key2 < t.key2));
    }

    bool operator >= (const Test &t)
    {
        return !(*this < t);
    }

    bool operator > (const Test &t)
    {
        return (key1 > t.key1) || ((key1 == t.key1) && (key2 > t.key2));
    }

    bool operator <= (const Test &t)
    {
        return !(*this > t);
    }

};
//只要大小关系的定义明确，多关键字和单关键字排序就没有本质的差别了
int main()
{
    Test t1(3, 4);
    Test t2(3, 5);

    cout << (t1 < t2) << endl;

    return 0;
}