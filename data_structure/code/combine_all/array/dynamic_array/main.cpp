#include <iostream>
#include "static_link_list.h"
#include "dynamic_array.h"

using namespace std;
using namespace DTLib;

int main(int argc, char **argv)
{
    DynamicArray< DynamicArray<int> > d; // 二维数组的定义

	d.resize(3); //这个二维数组有3行

	for (int i = 0; i < d.length(); i++) {
		// d[i].resize(3); //每一行有3个元素
		d[i].resize(i + 1); // 构建不规则的二维数组
	}

	for (int i = 0; i < d.length(); i++) {
		for (int j = 0; j < d[i].length(); j++) {
			d[i][j] = i * j;
		}
	}

	for (int i = 0; i < d.length(); i++) {
		for (int j = 0; j < d[i].length(); j++) {
			cout << d[i][j] << " ";
		}
		cout << endl;
	}


	return 0;
}
