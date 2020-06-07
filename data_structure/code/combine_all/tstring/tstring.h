#ifndef TSTRING_H
#define TSTRING_H

#include "object.h"

namespace DTLib{

class TString : public Object {
protected:
    char *m_str;
    int m_length;

    void init(const char *s);
    bool equal(const char *l, const char *r, int len) const;

    // kmp算法
    static int *make_pmt(const char *p);
    static int kmp(const char *s, const char *p);

public:
    TString();
    TString(const char *s);
    TString(const TString &s);
    TString(char c);
    int length() const;
    const char *str() const;

    /* kmp算法的应用 */
    int indexOf(const char *s);  // 查找子串s在字符串中的位置
    int indexOf(const TString &s);
    TString &remove(int i, int len); // 将字符串中的字串s删除
    TString &remove(const char *s); // 函数重载
    TString &remove(const TString &s); // 函数重载
    TString operator - (const TString &s) const;    // 定义字符串减法
    TString operator - (const char *s) const;
    TString &operator -= (const TString &s);
    TString &operator -= (const char *s);
    TString &replace(const char *t, const char *s); // 将字符串中的字串t替换为s
    TString &replace(const TString &t, const char *s);
    TString &replace(const char *t, const TString &s);
    TString &replace(const TString &t, const TString &s);
    /* 字符串类中的常用成员函数 */
    TString sub(int i, int len) const; // 从字符串中创建字串

    /* 字符串类中的常用成员函数 */
    bool startWith(const char *s) const;    // 判断字符串是否以s开头
    bool startWith(const TString &s) const;
    bool endOf(const char *s) const;        // 判断字符串是否以s结束
    bool endOf(const TString &s) const;
    TString &insert(int i, const char *s);    // 在字符串的位置i处插入s
    TString &insert(int i, const TString s);
    TString &trim();          // 去掉字符串两端的空白
    char &operator [] (int i); // 操作符重载函数，访问指定下标的字符
    char operator [] (int i) const;

    /* 比较操作符重载函数 */
    bool operator == (const TString &s) const;
    bool operator == (const char *s) const;
    bool operator != (const TString &s) const;
    bool operator != (const char *s) const;
    bool operator > (const TString &s) const;
    bool operator > (const char *s) const;
    bool operator < (const TString &s) const;
    bool operator < (const char *s) const;
    bool operator >= (const TString &s) const;
    bool operator >= (const char *s) const;
    bool operator <= (const TString &s) const;
    bool operator <= (const char *s) const;
    /* 加法操作符重载函数 */
    TString operator + (const TString &s) const;
    TString operator + (const char *s) const;
    TString &operator += (const TString &s);
    TString &operator += (const char *s);
    /* 赋值操作符重载函数 */
    TString &operator = (const TString &s);
    TString &operator = (const char *s);
    TString &operator = (const char c);

    ~TString();

};
}

#endif