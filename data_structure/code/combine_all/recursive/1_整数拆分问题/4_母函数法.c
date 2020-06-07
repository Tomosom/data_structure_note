/*

下面我们从另一个角度，即“母函数”的角度来考虑这个问题。

    所谓母函数，即为关于x的一个多项式G(x)：

    有G(x) = a0 + a1*x + a2*x^2 + a3*x^3 + ......

    则我们称G(x)为序列(a0, a1, a2,.....)的母函数。关于母函数的思路我们不做更过分析。

    我们从整数划分考虑，假设n的某个划分中，1的出现个数记为a1，2的个数记为a2，.....，i的个数记为ai，

    显然有：ak <= n/k（0<= k <=n）

    因此n的划分数f(n,n)，也就是从1到n这n个数字抽取这样的组合，每个数字理论上可以无限重复出现，即个数随意，使它们的综合为n。显然，数字i可以有如下可能，出现0次（即不出现），1次，2次，......，k次等等。把数字i用（x^i）表示，出现k次的数字i用（x^(i*k)）表示，不出现用1表示。

    例如，数字2用x^2表示，2个2用x^4表示，3个2用x^6表示，k个2用x^2k表示。

    则对于从1到N的所有可能组合结果我们可以表示为：

    G(x) = ( 1 + x + x^2 + x^3 + ... + x^n)*(1 + x^2 + x^4 + x^6 + ....)....(1 + x^n)

            = g(x,1)*g(x,2)*g(x,3)*....*g(x,n)

            = a0 + a1*x + a2*x^2 +...+ an*x^n + ....//展开式

    上面的表达式中，每个括号内的多项式代表了数字i的参与到划分中的所有可能情况。因此，该多项式展开后，由于x^a *x^b = x^(a+b)，因此x^i就代表了i的划分，展开后（x^i）项的系数也就是i的所有划分个数，即f(n,n) = an。

    由此我们找到了关于整数划分的母函数G(x)；剩下的问题就是，我们需要求出G(x)的展开后的所有系数。

    为此，我们首先要做多项式乘法，对于我们来说，并不困难。我们把一个关于x的多项式用一个整数数组a[]表示，a[i]代表x^i的系数，即：

    g(x) = a[0] + a[1]x + a[2]x^2 + ... + a[n]x^n;

    则关于多项式乘法的代码如下，其中数组a和数组b表示两个要相乘的多项式，结果存储到数组c中。

*/

#include <stdio.h>  
#include<time.h>
  
#define N 10005
int c1[N];
int c2[N];  

unsigned long dynamic_GetPartitionCount(int n)  
{
    int i, j, k;

    for(i=0; i <= n; i++) {  
        c1[i] = 1;  
        c2[i] = 0;  
    }  
    for(i=2; i <= n; i++) {  
        for(j=0; j <= n; j++) {
            for(k=0; k + j <= n; k += i) {
                c2[k + j] += c1[j];
            }
        }  
        for(j = 0; j <= n; j++) {  
            c1[j] = c2[j];  
            c2[j] = 0;  
        }  
    }  

    return c1[n];  
}  

int main(int argc, char **argv)  
{  
    int n = 0;
    //int m = 0;
	clock_t begintime, endtime;
    unsigned long count;  
    while(1)  
    {  
        // %d输入，滤掉不必要的字符		
        while(scanf("%d", &n) == 0) {
            if (getchar() == 'q') {
                return 0;
            }
        }

		if(n <= 0) {
            return 0;  
		}

        //m = n;

		begintime = clock();	//计时开始
        count = dynamic_GetPartitionCount(n);  
		endtime = clock();	//计时结束
        
        printf("\n%ld\n", count);  
		printf("Running Time：%ldms\n\n", endtime-begintime);
    }
    return 0;  
}  
