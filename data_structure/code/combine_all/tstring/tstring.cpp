#include <cstring>
#include <cstdlib>
#include "tstring.h"
#include "exception.h"

namespace DTLib {

void TString::init(const char *s)
{
    m_str = strdup(s);

    if (m_str) {
        m_length = strlen(m_str);
    } else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create tstring object ...");
    }

}

TString::TString()
{
    init("");
}

TString::TString(const char *s)
{
    init(s ? s : "");
}

TString::TString(const TString &s)
{
    init(s.m_str);
}

TString::TString(char c)
{
    char s[] = {c, '\0'};
    init(s);
}

int TString::length() const
{
    return m_length;
}

const char *TString::str() const
{
    return m_str;
}

bool TString::equal(const char *l, const char *r, int len) const
{
    bool ret = true;
    for(int i = 0; i < len && ret; i++) {
        ret = ret && (l[i] == r[i]);
    }
    return ret;
}

/* 建立指定字符串的部分匹配表 */
int *TString::make_pmt(const char *p)    // O(n)
{
    int len = strlen(p);
    int *ret = static_cast<int *>(malloc(sizeof(int) * len));
    if (ret != NULL) {
        int ll = 0;
        ret[0] = 0;
        for(int i = 1; i < len; i++) {
            while ((ll > 0) && (p[ll] != p[i])) {
                ll = ret[ll-1];
            }

            if (p[ll] == p[i]) {
                ll++;
            }

            ret[i] = ll;
        }
    }

    return ret;
}

int TString::kmp(const char *s, const char *p)   // O(m + n)
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int *pmt = make_pmt(p); // O(m)
    
    if ((pmt != NULL) && (pl > 0) && (pl <= sl)) {
        for (int i = 0, j = 0; i < sl; i++) {   // O(n)
            // 该字符匹配不成功，查表
            while ((j > 0) && (s[i] != p[j])) {
                j = pmt[j - 1];
            }

            if (s[i] == p[j]) {
                j++;
            }

            // 查找到
            if (j == pl) {
                ret = i + 1 - pl;
                break;
            }
        }
    }

    free(pmt);

    return ret;
}

/* kmp算法的应用 */
int TString::indexOf(const char *s)  // 查找子串s在字符串中的位置
{
    return kmp(m_str, s ? s : "");
}

int TString::indexOf(const TString &s)
{
    return kmp(m_str, s.m_str);
}

TString &TString::remove(int i, int len)
{
    if ((i >= 0) && (i <= m_length)) {
        int n = i;
        int m = i + len;

        while((n < m) && (m < m_length)) {
            m_str[n++] = m_str[m++];
        }
        m_str[n] = '\0';
        m_length = n;
    }
    return *this;
}

TString &TString::remove(const char *s)   // 将字符串中的字串s删除
{
    return remove(indexOf(s), s ? strlen(s) : 0);
}

TString &TString::remove(const TString &s)
{
    return remove(indexOf(s), s.length()); 
}

TString TString::operator - (const TString &s) const    // 定义字符串减法
{
    return TString(*this).remove(s);
}
TString TString::operator - (const char *s) const
{
    return TString(*this).remove(s);
}
TString &TString::operator -= (const TString &s)
{
    return remove(s);
}
TString &TString::operator -= (const char *s)
{
    return remove(s);
}

TString &TString::replace(const char *t, const char *s) // 将字符串中的字串t替换为s
{
    int index = indexOf(t);
    if (index >= 0) {
        remove(t);
        insert(index, s);
    }
    return *this;
}
TString &TString::replace(const TString &t, const char *s)
{
    return replace(t.m_str, s);
}
TString &TString::replace(const char *t, const TString &s)
{
    return replace(t, s.m_str);
}
TString &TString::replace(const TString &t, const TString &s)
{
    return replace(t.m_str, s.m_str);
}

/* 字符串类中的常用成员函数 */
TString TString::sub(int i, int len) const
{
    TString ret;

    if ((i >= 0) && (i <= m_length)) {
        // 归一化
        if (len < 0) len = 0;
        if (len + i > m_length) len = m_length - i;

        char *str = reinterpret_cast<char *>(malloc(len + 1));
        strncpy(str, m_str + i, len);
        str[len] = '\0';

        ret = str;
    } else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
    }
    return ret;
}

/* 字符串类中的常用成员函数 */
bool TString::startWith(const char *s) const    // 判断字符串是否以s开头
{
    bool ret = (s != NULL);
    if (ret) {
        int len = strlen(s);
        ret = (len < m_length) && equal(m_str, s, len);
    }

    return ret;
}
bool TString::startWith(const TString &s) const
{
    return startWith(s.m_str);
}
bool TString::endOf(const char *s) const        // 判断字符串是否以s结束
{
    bool ret = (s != NULL);
    if (ret) {
        int len = strlen(s);
        char *str = m_str + (m_length - len);
        ret = (len < m_length) && equal(str, s, len);
    }

    return ret;
}
bool TString::endOf(const TString &s) const
{
    return endOf(s.m_str);
}

TString &TString::insert(int i, const char *s)    // 在字符串的位置i处插入s, 返回引用是为了实现链式操作
{
    if ((i >= 0) && (i <= m_length)) {
        if ((s != NULL) && (s[0] != '\0')) {
            int len = strlen(s);
            char *str = reinterpret_cast<char *>(malloc(m_length + len + 1));
            if (str != NULL) {
                strncpy(str, m_str, i);
                strncpy(str + i, s, len);
                strncpy(str + i + len, m_str + i, m_length - i);
                str[m_length + len] = '\0';
                free(m_str);
                m_str = str;
                m_length = m_length + len;
            } else {
                THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert TString values ...");
            }
        }
    } else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
    }
    return *this;
}
TString &TString::insert(int i, const TString s)
{
    return insert(i, s.m_str);
}

TString &TString::trim() // 去掉字符串两端的空白, 返回引用, 方便链式调用
{
    int b = 0;
    int e = m_length - 1;

    while(m_str[b] == ' ') b++;
    while(m_str[e] == ' ') e--;

    if (b == 0) {
        m_str[e + 1] = '\0';
        m_length = e + 1;
    } else {
        for (int i = 0, j = b; j <= e; i++, j++) {
            m_str[i] = m_str[j];
        }

        m_str[e - b + 1] = '\0';
        m_length = e - b + 1;
        
    }
    return *this;
}

char &TString::operator [] (int i) // 操作符重载函数，访问指定下标的字符, 返回引用表示可以被赋值（出现在赋值符号的左边）
{
    if ((i >= 0) && (i < m_length))
    {
        return m_str[i];
    } else {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid ...");
    }
}
char TString::operator [] (int i) const
{
    return (const_cast<TString &>(*this))[i]; // 剔除const属相
}

/* 比较操作符重载函数 */
bool TString::operator == (const TString &s) const
{
    return (strcmp(m_str, s.m_str) == 0);
}
bool TString::operator == (const char *s) const
{
    return (strcmp(m_str, s ? s : "") == 0);
}
bool TString::operator != (const TString &s) const
{
    return !(*this == s);
}
bool TString::operator != (const char *s) const
{
    return !(*this == s ? s : "");
}
bool TString::operator > (const TString &s) const
{
    return (strcmp(m_str, s.m_str) > 0);
}
bool TString::operator > (const char *s) const
{
    return (strcmp(m_str, s ? s : "") > 0);
}
bool TString::operator < (const TString &s) const
{
    return (strcmp(m_str, s.m_str) < 0);
}
bool TString::operator < (const char *s) const
{
    return (strcmp(m_str, s ? s : "") < 0);
}
bool TString::operator >= (const TString &s) const
{
    return (strcmp(m_str, s.m_str) >= 0);
}
bool TString::operator >= (const char *s) const
{
    return (strcmp(m_str, s ? s : "") >= 0);
}
bool TString::operator <= (const TString &s) const
{
    return (strcmp(m_str, s.m_str) <= 0);
}
bool TString::operator <= (const char *s) const
{
    return (strcmp(m_str, s ? s : "") <= 0); 
}

/* 加法操作符重载函数 */
TString TString::operator + (const TString &s) const
{
    return (*this + s.m_str);
}
TString TString::operator + (const char *s) const
{
    TString ret;
    int len = m_length + strlen(s ? s : "");
    char *str = reinterpret_cast<char *>(malloc(len + 1));
    if (str) {
        strcpy(str, m_str);
        strcat(str, s ? s : "");
        free(ret.m_str);
        ret.m_str = str;
        ret.m_length = len;
    } else {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add TString values ...");
    }
    return ret;
}
TString &TString::operator += (const TString &s)
{
    return (*this = *this + s);
}
TString &TString::operator += (const char *s)
{
    return (*this = *this + s);
}

/* 赋值操作符重载函数 */
TString &TString::operator = (const TString &s)
{
    return (*this = s.m_str);
}
TString &TString::operator = (const char *s)
{
    if (m_str != s) {
        char *str = strdup(s ? s : "");
        if (str) {
            free(m_str);
            m_str = str;
            m_length = strlen(m_str);

        } else {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to assign new TString values ...");
        }
    }

    return *this;
}
TString &TString::operator = (const char c)
{
    char s[] = {c, '\0'};
    return (*this = s);
}

TString::~TString()
{
    free(m_str);
}

}