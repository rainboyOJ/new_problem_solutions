/*-------------------------------------------------
 *  windy 数 - 非递归(递推)数位DP
 *  Author:Rainboy
 *  2018-07-08 08:52
 *-------------------------------------------------*/
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;


int a,b;

/* f[i][j]: i位数、最高位为j的windy数个数 */
/* 条件: 相邻两位数字差 >= 2 */
int f[12][10] = {0};
int str[100];    /* 拆解后的数字, 低位在前 */
int cnt;         /* 数字位数 */

/* 将 n 拆成数字存到 str[1..cnt), str[1] 为个位 */
/* 例: n=123 -> str[1]=3, str[2]=2, str[3]=1, cnt=4 */
void div(int n){
    cnt = 1;
    if( n == 0) str[cnt] =0,cnt++;
    while( n > 0){
        str[cnt++] = n % 10;
        n = n / 10;
    }
}

/* 预处理 f 表 */
void init(){
    int i,j,k;

    /* 边界: 1位数, 最高位取 0-9 都只有 1 个 */
    for(i=0;i<=9;i++) f[1][i] = 1; 

    /* 递推: 填 i 位数, 枚举第 i 位 j 和第 i-1 位 k */
    for(i=2;i<=11;i++)
        for(j=0;j<=9;j++)
            for(k=0;k<=9;k++)
                if( abs(j-k) >=2)
                    f[i][j] += f[i-1][k];
}


/* 计算 [0, n] 内 windy 数的个数 */
int calc(int n){
    div(n);

    int i,j,k,res = 0;

    /* 1. 位数少于 n 的数 (位数 < cnt-1) */
    /*    最高位不能为 0, 故 j 从 1 开始 */
    for(i=1;i<cnt-1;i++) 
        for(j=1;j<=9;j++)
            res += f[i][j];

    /* 2. 位数与 n 相同, 但最高位 < str[cnt-1] */
    for(i=1;i<str[cnt-1];i++)
        res+= f[cnt-1][i];

    /* 3. 从高位到低位固定前缀, 统计剩余位 */
    for(i=cnt-2;i>=1;i--)
    {
        /* 当前位取 [0, str[i]-1], 且与上一位差 >= 2 */
        for(j=0;j<str[i];j++)
            if( abs(j-str[i+1]) >=2 )
                res += f[i][j];

        /* n 自己的这两位差 < 2, 后续不可能满足, 提前退出 */
        if( abs(str[i] - str[i+1]) < 2)
            break;

        /* 所有位都满足条件, n 本身也是 windy 数 */
        if( i== 1)
            res+=1;
    }
    return res;

}

int main(){
    init();
    scanf("%d%d",&a,&b);
    int ans;
    ans = calc(b) - calc(a-1);
    printf("%d\n",ans);
    return 0;
}
