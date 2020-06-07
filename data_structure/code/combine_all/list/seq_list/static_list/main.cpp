#include <iostream>
#include "static_list.h"
#include "dynamic_list.h"
using namespace std;
using namespace DTLib;

#define DYNAMICLIST 0

int main(int argc, char **argv)
{
#if DYNAMICLIST
	DynamicList<int> l(5);
	// DynamicList<int> n(5);
	// n = l;

#else
	StaticList<int, 5> l;
	// StaticList<int, 5> n;
	// n = l;

#endif

	for (int i = 0; i < l.capacity(); i++) {
		l.insert(0, i); // l.insert(i);
	}
	
	for (int i = 0; i < l.length(); i++) {
		cout << l[i] << endl;
	}
	
	l[0] *= l[0];
	for (int i = 0; i < l.length(); i++) {
		cout << l[i] << endl;
	}

	try {
		l[5] = 5;
	}
	catch(const Exception &e) {
		cout << e.message() << endl;
		cout << e.location() << endl;
#if DYNAMICLIST
		l.resize(10);
		l.insert(5, 30);
		
		for (int i = 0; i < l.length(); i++) {
			cout << l[i] << endl;
		}	
#endif
	}
#if DYNAMICLIST
	l[5] = 5;
	
	for (int i = 0; i < l.length(); i++) {
		cout << l[i] << endl;
	}		

	l.resize(3);

	for (int i = 0; i < l.length(); i++) {
		cout << l[i] << endl;
	}
#endif
	return 0;
	
}
