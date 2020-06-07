#include <iostream>
#include "static_queue.h"

using namespace std;
using namespace DTLib;

// 类似的，当数据元素为类类型时，StaticQueue的对象在创建时，会多次调用元素类型的构造函数，影响效率
// 所以需要实现链式队列

int main(int argc, char **argv)
{
    StaticQueue<int, 5> queue;
    for(int i = 0; i < 5; i++) {
        queue.add(i);
    }

    while(queue.length() > 0) {
        cout << queue.front() << endl;
        queue.remove();
    }
    
    return 0;
}
