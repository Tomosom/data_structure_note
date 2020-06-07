#include <iostream>
#include "dual_link_list.h"

using namespace std;
using namespace DTLib;

int main(int argc, char **argv)
{
	DualLinkList<int> dl;

	for (int i = 0; i < 5; i++) {
		dl.insert(0, i);
		dl.insert(0, 5);
	}

	//for (int i = 0; i < dl.length(); i++) { // O(n2)
	for (dl.move(0); !dl.end(); dl.next()) { // O(n)
		//cout << dl.get(i) << endl;
		cout << dl.current() << endl;
	}	

	cout << "begin" << endl;
	for (dl.move(dl.length() - 1); !dl.end(); dl.prev()) { // O(n)
		cout << dl.current() << endl;
	}	
	cout << "end" << endl;

	// 删除链表中数值为5的元素
	dl.move(dl.length() - 1);
	while(!dl.end()) {
		if (dl.current() == 5) {
			//cout << dl.current() << endl;

			dl.remove(dl.find(dl.current()));
		} else {
			dl.prev();
		}
	}

	//for (int i = 0; i < dl.length(); i++) { // O(n2)
	for (dl.move(0); !dl.end(); dl.next()) { // O(n)
		//cout << dl.get(i) << endl;
		cout << dl.current() << endl;
	}
	return 0;

}
