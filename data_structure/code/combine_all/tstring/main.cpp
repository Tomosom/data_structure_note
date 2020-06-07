#include <iostream>
#include "tstring.h"

using namespace std;
using namespace DTLib;

/* 字符串常规造作测试 */
void test_1()
{
    cout << "test_1() begin ..." << endl;

    TString s;
    s = 'D';
    cout << s.str() << endl;
    cout << s.length() << endl;
    cout << (s == 'D') << endl;
    cout << (s > "CCC") << endl;

    s += "Tao jia";
    cout << s.str() << endl;
    cout << s.length() << endl;
    cout << (s == "DTao jia") << endl;

    cout << "test_1() end ..." << endl;
}

/* 字符串常规造作测试 */
void test_2()
{
    cout << "test_2() begin ..." << endl;

    TString a[] = {"e", "d", "c", "b", "a"};
    TString min = a[0];
    
    for(int i = 0; i < 5; i++) {
        if (min > a[i]) {
            min = a[i];
        }
    }

    cout << "min = " << min.str() << endl;

    cout << "test_2() end ..." << endl;
}

/* 数组访问操作符重载函数测试 */
void test_3()
{ 
    TString s = "Tao Jia Quan";
    for(int i = 0; i < s.length(); i++) {
        cout << s[i] << endl;
    }
}

/* startWith和endOf函数测试 */
void test_4()
{
    TString s = "Tao Jia Quan";
    
    cout << s.startWith("Tao") << endl;
    cout << s.endOf("Quan") << endl;
    // for(int i = 0; i < s.length(); i++) {
    //     cout << s[i] << endl;
    // }
}

/* 插入字符串函数insert测试 */
void test_5()
{
    TString s = "";
    
    s.insert(0, "Tao ");
    s.insert(4, "software");
    s.insert(4, "jia quan ");
    cout << s.str() << endl;
    cout << s.insert(4, "jia quan ").str() << endl;
}

/* trim函数测试 */
void test_6()
{
    TString s = "   abc    ";
    
    if (s.trim().insert(0, "Tao ").endOf("abc") && s.startWith("Tao")) { // 链式调用的操作
        cout << "[" << s.str() << "]" << endl;
    }
}

/* KMP test : indexOf */
void test_7()
{
    TString s = "ababax";
    cout << s.indexOf("ax") << endl;
}

/* KMP test : remove */
void test_8()
{
    TString s = "abcde";
    TString del = "abc";

    //cout << s.remove(2,2).length() << endl;
    //cout << s.remove("abc").str() << endl;
    cout << s.remove(del).str() << endl;

}

/* KMP test : operator -  */
void test_9()
{
    TString s = "abcde";
    TString del = "abc";

    cout << s.str() << endl;
    cout << (s - del).str() << endl;

    s -= "cd";
    cout << s.str() << endl;

}

/* KMP test : replace */
void test_10()
{
    TString s = "ababax";
    
    s.replace("baba", "xyz");

    cout << s.str() << endl;
}

// 从字符串中创建字串
void test_11()
{
    TString s = "ababax";
    
    TString s1 = s.sub(3, 2);

    cout << s1.str() << endl;
}

int main(int argc, char **argv)
{
    //test_1();
    //test_2();
    //test_3();
    //test_4();
    //test_5();
    //test_6();
    //test_7();
    //test_8();
    //test_9();
    //test_10();
    test_11();

    return 0;
}
