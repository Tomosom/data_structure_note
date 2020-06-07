#include <iostream>
#include "static_link_list.h"

using namespace std;
using namespace DTLib;

int main(int argc, char **argv)
{
    StaticLinkList<int, 5> list;

    for (int i = 0; i < 5; i++) {
        list.insert(0, i);
    }

//    for(int i = 0; i < list.length(); i++) {
//        cout << list.get(i) << endl;
//    }

    try {
        list.insert(6);
    }
    catch(const Exception &e) {
        cout << e.message() << endl;

    }

    for (list.move(0); !list.end(); list.next()) {
        cout << list.current() << endl;
    }
    cout << "-----" << endl;
    for (list.move(0, 2); !list.end(); list.next()) {
        cout << list.current() << endl;
    }
	return 0;
}