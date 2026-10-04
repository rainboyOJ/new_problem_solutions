/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:48
 * update_at: 2026-10-05 04:48
 */

#include <cstdio>

typedef long long ll;

const int MAXA = 1000000 + 5;
const int MOD = 1000;

// fib[i] = 菲波那契数列第 i 项对 1000 取模的结果
ll fib[MAXA];

int main() {
    // 预计算：所有询问共享同一张表，先递推到最大的可能下标
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i <= MAXA - 5; ++i) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % MOD; // 同余对加法封闭，边算边取模
    }

    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 1; i <= n; ++i) {
        int a;
        scanf("%d", &a);
        printf("%lld\n", fib[a]); // 每问 O(1) 查表
    }
    return 0;
}
