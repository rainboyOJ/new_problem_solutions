/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:50
 * update_at: 2026-10-05 03:50
 */
#include <cstdio>

typedef long long ll;

ll n;                 // 输入的项号
ll fib_value[105];    // fib_value[i] = 零起编号斐波那契 F(i)，F(0)=0、F(1)=1
char computed[105];   // computed[i] 标记 F(i) 是否已经算过，只有 0/1，用 char 省内存

// 记忆化递归：返回 F(i)，每个下标只计算一次
ll fib(ll i) {
    if (i < 2) return i;
    if (computed[i]) return fib_value[i];
    fib_value[i] = fib(i - 1) + fib(i - 2);
    computed[i] = 1;
    return fib_value[i];
}

int main() {
    scanf("%lld", &n);

    // 题面数列 0,1,1,2,3,5,... 首项是 0，第 n 项对应零起编号的 F(n-1)
    printf("%lld\n", fib(n - 1));

    return 0;
}
