#include <iostream>
#include "static_array.h"
#include "dynamic_array.h"

using namespace std;
using namespace DTLib;

#define DYNAMICARRAY 0

int main(int argc, char **argv)
{
#if DYNAMICARRAY

    DynamicArray<int> s1(5);

    for (int i = 0; i < s1.length(); i++) {
        s1[i] = i * i;
    }

    for (int i = 0; i < s1.length(); i++) {
        cout << s1[i] << endl;
    }

    DynamicArray<int> s2(10);

    s2 = s1;

    s2.resize(3);

    for (int i = 0; i < s2.length(); i++) {
        cout << s2[i] << endl;
    }

    // 数组越界尝试
    try {
        s2[6] = 100;
    }
    catch (const Exception &e) {
        cout << e.message() << endl;
    }


#if 0
    // 原生数组越界不会提示任何信息
    int s3[5];
    s3[6] = 100;
#endif

#else

    StaticArray<int, 5> s1;

    for (int i = 0; i < s1.length(); i++) {
        s1[i] = i * i;
    }

    for (int i = 0; i < s1.length(); i++) {
        cout << s1[i] << endl;
    }

    StaticArray<int, 5> s2;

    s2 = s1;

    for (int i = 0; i < s2.length(); i++) {
        cout << s2[i] << endl;
    }

    // 数组越界尝试
    try {
        s2[6] = 100;
    }
    catch (const Exception &e) {
        cout << e.message() << endl;
    }

#if 0
    // 原生数组越界不会提示任何信息
    int s3[5];
    s3[6] = 100;
#endif

#endif
	return 0;

}
