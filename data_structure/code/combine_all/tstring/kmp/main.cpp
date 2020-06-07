#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

/* 建立指定字符串的部分匹配表 */
int *make_pmt(const char *p)    // O(n)
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

int kmp(const char *s, const char *p)   // O(m + n)
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

// 朴素解法
int sub_str_index(const char *s, const char *p) // O(m * n)
{
    int ret = -1;
    int sl = strlen(s);
    int pl = strlen(p);
    int len = sl - pl;

    for(int i = 0; (ret < 0) && (i <= len); i++) {
        bool equal = true;
        for (int j = 0; equal && (j < pl); j++) {
            equal = equal && (s[i + j] == p[j]);
        }
        ret = (equal ? i : -1);
    }

    return ret;
}

int main(int argc, char **argv)
{
    int *pmt = make_pmt("ABCDABD");

    for (int i = 0; i < strlen("ABCDABD"); i++) {
        cout << i << ":" << pmt[i] << endl;
    }
    //  两种方法对比
    cout << kmp("ababax", "ax") << endl;
    cout << sub_str_index("ababax", "ax") << endl;

    return 0;
}
