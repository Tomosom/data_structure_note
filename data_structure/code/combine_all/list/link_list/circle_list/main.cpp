#include <iostream>
#include "circle_list.h"

using namespace std;
using namespace DTLib;


 /* 约瑟夫环问题
    n : 多少个人玩这个游戏
    s : 从第几个人开始报数
    m : 报到第几个数
  */
void josephus(int n, int s, int m)
{
    CircleList<int> c;
    int i = 0;
    for(i = 1; i <= n; i++) {
        c.insert(i);
    }

    for (c.move(0), i = 0; i < c.length(); c.next(), i++) { // 单向循环链表的遍历方法
        cout << c.current() << endl;
    }

    cout << "--------" << endl;

    c.move(s-1, m-1);

    while (c.length() > 0) {
        c.next();
        cout << c.current() << endl;
        c.remove(c.find(c.current()));
    }

}

int main(int argc, char **argv)
{

    josephus(41, 1, 3);

	return 0;

}
