#include <stdio.h>  
#include<time.h>
  
#define MAXNUM 100            //最高次数  
unsigned  long ww[MAXNUM*11][MAXNUM*11];

//递归法求解整数划分  
unsigned long dynamic_GetPartitionCount(int n, int max)  
{  
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=i;j++) {  
            if(j==1|| i==1) {  
                ww[i][j]=1;  
            } else {  
                if(j == i) {
                    ww[i][j] = ww[i][j-1]+1;  
                } else if((i - j) < j) { 
                    ww[i][j] = ww[i-j][i-j]+ww[i][j-1];  
                } else {
                    ww[i][j] = ww[i-j][j]+ww[i][j-1];
                }
            }  
        }
    }
    return ww[n][max];  
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
