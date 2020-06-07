#include <stdio.h>  
#include<time.h>
  
#define MAXNUM 100            //最高次数  
  
//递归法求解整数划分  
unsigned long GetPartitionCount(int n, int max)  
{  
    if(n == 1 || max == 1) {  
        return 1;  
    }  
    if(n < max) {  
        return GetPartitionCount(n, n);  
    }  
    if(n == max) {  
        return 1 + GetPartitionCount(n, n - 1);  
    } else {  
        return GetPartitionCount(n - max, max) + GetPartitionCount(n, max - 1);  
    }  
}  

int main(int argc, char **argv)  
{  
    int n = 0;
    int m = 0;
	clock_t begintime, endtime;
    unsigned long count;  
    while(1) {  
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
        count = GetPartitionCount(n, m);  
		endtime = clock();	//计时结束
        
        printf("\n%ld\n", count);  
		printf("Running Time：%ldms\n\n", endtime-begintime);
    }
    return 0;  
}  
