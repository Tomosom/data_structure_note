#include <stdio.h>  
#include<time.h>
  
#define MAXNUM 100            //最高次数  
unsigned  long ww[MAXNUM*11][MAXNUM*11];

//递归法求解整数划分  
unsigned long dynamic_GetPartitionCount(int n, int max)  
{  
    if(n == 1 || max == 1) {  
        ww[n][max] = 1;  
        return 1;  
    }  
    if(n < max) {  
        ww[n][n] = ww[n][n] ? ww[n][n] : dynamic_GetPartitionCount(n, n);  
        return ww[n][n];  
    }  
    if(n == max) {  
        ww[n][max] = ww[n][n - 1] ? 1 + ww[n][n - 1] : 1 + dynamic_GetPartitionCount(n, n - 1);  
        return ww[n][max];  
    } else {  
        ww[n][max] = ww[n - max][max] ? (ww[n - max][max]) : dynamic_GetPartitionCount(n - max, max);  
        ww[n][max] += ww[n][max - 1] ? (ww[n][max-1]) : dynamic_GetPartitionCount(n, max - 1);      
        return ww[n][max];  
    }  
}  

int main(int argc, char **argv)  
{  
    int n = 0;
    int m = 0;
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

        m = n;

		begintime = clock();	//计时开始
        count = dynamic_GetPartitionCount(n, m);  
		endtime = clock();	//计时结束
        
        printf("\n%ld\n", count);  
		printf("Running Time：%ldms\n\n", endtime-begintime);
    }
    return 0;  
}  
