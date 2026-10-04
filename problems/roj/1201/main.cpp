/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:26
 * update_at: 2026-10-05 05:26
 */
#include <cstdio>

typedef long long ll;

ll fib[25]; // fib[i] 表示菲波那契数列第 i 项，下标从 1 开始和题面对应

// 自底向上递推预处理：F(1)=F(2)=1，F(a)=F(a-1)+F(a-2)
void init_fib() {
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i <= 20; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];
}

int main() {
    init_fib(); // a<=20，预处理一遍后面每个询问 O(1) 回答

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        int a;
        scanf("%d", &a);
        printf("%lld\n", fib[a]);
    }
    return 0;
}
