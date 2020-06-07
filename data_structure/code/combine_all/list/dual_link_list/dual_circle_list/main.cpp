#include <iostream>

#include "dual_circle_list.h"

using namespace std;
using namespace DTLib;

int main(int argc, char **argv)
{
    DualCircleList<int> dcl;
    for(int i = 0; i < 5; i++) {
#if 0 // 头插
        dcl.insert(0, i);
        dcl.insert(0, 5);
#else // 尾插
        dcl.insert(i);
        dcl.insert(5);        
#endif
    }

    cout << "begin" << endl;
    
    dcl.move(dcl.length() - 1);

    while(dcl.find(5) != -1) {
        if (dcl.current() == 5) {
            cout << dcl.current() << endl;
            dcl.remove(dcl.find(dcl.current()));
        } else {
            dcl.prev();
        }
    }

    cout << "end" << endl;


#if 0
    //for(dcl.move(0); !dcl.end(); dcl.next()) { // error
    //for (int i = 0; i < dcl.length(); i++) {
    for (int i = 0; i < 10; i++) {    
        cout << dcl.get(i) << endl;
    }
#else
    int i;
    //for(dcl.move(0); !dcl.end(); dcl.next()) { //error
    //for (dcl.move(0), i = 0; i < dcl.length(); dcl.next(), i++) { // 正向打印
    for (dcl.move(dcl.length() - 1), i = 0; i < dcl.length(); dcl.prev(), i++) { // 反向打印
        cout << dcl.current() << endl;
    }
#endif
    return 0;
}


